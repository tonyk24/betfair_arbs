#include <stdexcept>
#include <algorithm>

#include <QString>
#include <QElapsedTimer>
#include <QCoreApplication>

#include "betcontrollerlib.h"
#include "factory/bffilterfactory.h"

#include "sleeper.h"

BetControllerLib::BetControllerLib(QObject *parent, Config *config)
  : m_config(config),
    m_accountsHandler(0, m_config->getConfiguredMaxExposure()),
    m_betHandler(0, &m_accountsHandler, &m_eventStats, m_config),
    m_marketsData(m_config->getRetrieveGroups()),
    m_quit(false),
    m_debugMsgListEvents(false),
    m_debugMsgListEventsDetailed(false),
    m_debugMsgListEventBets(false),
    m_debugMsgListEventBetsMarket(false),
    m_debugMsgListeEventDetailsSlot(0),
    m_debugMsgListeEventDetailsIndex(0),
    m_debugMsgListeEventDetailsMarket(""),
    m_debugMsgTakeBet(false),
    m_debugMsgTakeBetEventId(""),
    m_debugMsgTakeBetSelId(0),
    m_debugMsgTakeBetSide(BfSide::BACK),
    m_debugMsgListAccount(false),
    m_debugMsgListEventDataConsumer(false),
    m_debugMsgListConfig(false)
{
  Q_UNUSED(parent);

  m_marketBookApi = new MarketBookApi(0, m_config->getBfConfig());
  m_eventsApi = new EventsApi(0, m_config->getBfConfig());
  m_keepAliveApi = new KeepAliveApi(0, m_config->getBfConfig());
  m_placeOrdersApi = new PlaceOrdersApi(0, m_config->getBfConfig());
  m_accountsApi = new AccountsApi(0, m_config->getBfConfig());
  m_marketCatalogueApi = new MarketCatalogueApi(0, m_config->getBfConfig());

  QObject::connect(m_eventsApi, SIGNAL(valueChanged(std::list<BfEvent>)),
                   this, SLOT(receivedEvents(std::list<BfEvent>)));
  QObject::connect(m_marketCatalogueApi, SIGNAL(valueChanged(QString, std::list<BetfairMarket>)),
                   this, SLOT(receivedMarketCatalogue(QString, std::list<BetfairMarket>)));
  QObject::connect(m_marketBookApi, SIGNAL(valueChanged(std::list<BetfairMarket>)),
                   this, SLOT(receivedMarketBookData(std::list<BetfairMarket>)));
  QObject::connect(m_placeOrdersApi, SIGNAL(placeOrdersResponse(BfPlaceExecutionReport)),
                   this, SLOT(receivedPlaceOrdersRsp(BfPlaceExecutionReport)));

  QObject::connect(m_accountsApi, SIGNAL(valueChanged(BfAccountDetailsRsp)),
                   this, SLOT(receivedAccountDetails(BfAccountDetailsRsp)));
  QObject::connect(m_accountsApi, SIGNAL(valueChanged(BfAccountFundsRsp)),
                   this, SLOT(receivedAccountFunds(BfAccountFundsRsp)));

  m_marketDataUpdateTimer = new QTimer(this);
  m_marketDataUpdateTimer->start(int(m_config->getPerRetrieveGroupFrequencyS()*1000.0));
  QObject::connect(m_marketDataUpdateTimer, SIGNAL(timeout()), this, SLOT(updateMarketBook()));

  m_keepAliveTimer = new QTimer(this);
  QObject::connect(m_keepAliveTimer, SIGNAL(timeout()), this, SLOT(keepAliveTimeout()));

  // ERRORS
  QObject::connect(m_marketBookApi, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
  QObject::connect(m_eventsApi, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
  QObject::connect(m_keepAliveApi, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
  QObject::connect(m_placeOrdersApi, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
  QObject::connect(m_accountsApi, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
  QObject::connect(m_marketCatalogueApi, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));

  qDebug() << "BetControllerLib()";

  m_eventDataConsumer = new EventDataConsumer();
  QObject::connect(m_eventDataConsumer, SIGNAL(threadError(QString)),
                   this, SLOT(threadError(QString)));
  QObject::connect(m_eventDataConsumer, SIGNAL(debugMessage(QString)),
                   this, SLOT(threadMessage(QString)));
  m_eventDataConsumer->start();
}

BetControllerLib::~BetControllerLib() {
  delete m_marketDataUpdateTimer;
  delete m_keepAliveTimer;

  m_eventDataConsumer->quit();
  m_eventDataConsumer->wait();
  delete m_eventDataConsumer;


  delete m_marketBookApi;
  delete m_eventsApi;
  delete m_keepAliveApi;
  delete m_placeOrdersApi;
  delete m_accountsApi;
  delete m_marketCatalogueApi;
}

void BetControllerLib::run() {
  qDebug() << "LogController::run()";
  QElapsedTimer timer;
  timer.start();

  qint64 lastTime = timer.elapsed()- 10*60*1000;

  QElapsedTimer timerListCurrentOrders;
  timerListCurrentOrders.start();

  qint64 lastTimeListCurrentOrders = timerListCurrentOrders.elapsed() - 2*1000;

  while (!m_quit) {
    // Update account details if needed
    if (m_accountsHandler.shouldSendRequest()) {
      qDebug() << "Requesting account funds...";
      m_accountsHandler.requestSent();
      m_accountsApi->getAccountFunds();
    }

    // Get new events every 10 minutes
    if (timer.elapsed() - lastTime > 10*60*1000) {
      qDebug() << "Requesting new events...";
      lastTime = timer.elapsed();
      BetfairMarketFilter marketFilter = BfFilterFactory::chooseEventsFilter();

      m_eventsApi->get(marketFilter);
      if (!m_keepAliveTimer->isActive()) {
        m_keepAliveTimer->start(2*60*60*1000);
      }
    }

    // Decide to stop getting markets, with condition
    // * No market data received for 5 minutes
    std::list<QString> activeEvents = m_marketsData.getActiveEvents();
    for (std::list<QString>::iterator itEvent = activeEvents.begin();
         itEvent != activeEvents.end();) {
      if (m_eventStats.subscribingEventMoreThan5MinutesAgo(*itEvent) &&
          !m_eventStats.marketMOOpen5MinutesAgo(*itEvent)) {
          qDebug() << "Stop getting markets for event (not saving results): " << *itEvent;
          m_marketsData.removeEvent(*itEvent);
          m_eventDataConsumer->abortEvent(*itEvent);
          itEvent = activeEvents.erase(itEvent);
      } else {
         itEvent++;
      }
    }

    // Decide to stop getting markets, with condition
    // * MO closed for at least 1 minutes
    for (std::list<QString>::iterator it = activeEvents.begin();
         it != activeEvents.end();) {
      if (m_eventStats.marketMOClosedFor1Minutes(*it)) {
        qDebug() << "1. Stop getting markets for event: " << *it;
        m_marketsData.removeEvent(*it);
        qDebug() << "2. Stop getting markets for event: " << *it;
        m_eventDataConsumer->finish(*it);
        qDebug() << "3. Stop getting markets for event: " << *it;
        it = activeEvents.erase(it);
      } else {
        it++;
      }
    }

    // Check for errors
    for (std::list<QString>::iterator it = activeEvents.begin();
         it != activeEvents.end(); it++) {
      if (m_eventStats.hasEventError(*it) > 0) {
        qDebug() << "ERROR: Found error in event, aborting...";
      }
    }

    // List current orders every 2 seconds
    if (timerListCurrentOrders.elapsed() - lastTimeListCurrentOrders > 2*1000) {
      qDebug() << "Requesting current orders...";
      // TODO: ......
    }

    if (m_debugMsgListEvents) {
      m_debugMsgListEvents = false;
      QString msg = m_marketsData.getActiveEventsStr();
      emit debugMsg(msg);
    }

    if (m_debugMsgListEventsDetailed) {
      m_debugMsgListEventsDetailed = false;
      QString msg = m_marketsData.getActiveEventsDetailsStr(m_debugMsgListeEventDetailsSlot);
      emit debugMsg(msg);
    }
    if (m_debugMsgListEventBets) {
      m_debugMsgListEventBets = false;
      QString msg = m_marketsData.getActiveEventBetsStr(m_debugMsgListeEventDetailsSlot,
                                                        m_debugMsgListeEventDetailsIndex);
      emit debugMsg(msg);
    }
    if (m_debugMsgListEventBetsMarket) {
      m_debugMsgListEventBetsMarket = false;
      QString msg = m_marketsData.getActiveEventBetsMarketStr(m_debugMsgListeEventDetailsSlot,
                                                              m_debugMsgListeEventDetailsIndex,
                                                              m_debugMsgListeEventDetailsMarket);
      emit debugMsg(msg);
    }
    if (m_debugMsgListAccount) {
      m_debugMsgListAccount = false;
      QString msg = m_accountsHandler.getDebugStr();
      emit debugMsg(msg);
    }
    if (m_debugMsgListEventDataConsumer) {

    }
    if (m_debugMsgListConfig) {
      m_debugMsgListConfig = false;
      QString msg = m_config->getDebugStr();
      emit debugMsg(msg);
    }

    QCoreApplication::processEvents();
  }
}

void BetControllerLib::aboutToQuitApp() {

}

void BetControllerLib::errorOccurred(BfApiNgException *ex) {
  qWarning() << "Receieved error:" << ", " << ex->toString();
  if (ex->m_errorType == BfApiNgException::API_NG_ERR) {
    if (ex->m_apiNgErrorCode == "TOO_MUCH_DATA") {
    } else if(ex->m_apiNgErrorCode == "INVALID_INPUT_DATA" ||
              ex->m_apiNgErrorCode == "INVALID_SESSION_INFORMATION" ||
              ex->m_apiNgErrorCode == "NO_APP_KEY" ||
              ex->m_apiNgErrorCode == "NO_SESSION" ||
              ex->m_apiNgErrorCode == "UNEXPECTED_ERROR" ||
              ex->m_apiNgErrorCode == "INVALID_APP_KEY" ||
              ex->m_apiNgErrorCode == "TOO_MANY_REQUESTS" ||
              ex->m_apiNgErrorCode == "REQUEST_SIZE_EXCEEDS_LIMIT" ||
              ex->m_apiNgErrorCode == "ACCESS_DENIED") {
      qWarning() << "Exiting: " << ex->toString();
      throw std::runtime_error(ex->toString().toStdString());
      return;
    } else if(ex->m_apiNgErrorCode == "SERVICE_BUSY") {
      // Do nothing
      return;
    } else if(ex->m_apiNgErrorCode == "TIMEOUT_ERROR") {
      // Do nothing
      return;
    } else {
      qWarning() << "Found unexpected API_NG_ERR error code..";
      qWarning() << "Exiting: " << ex->toString();
      throw std::runtime_error(ex->toString().toStdString());
      return;
    }
  }


  throw std::runtime_error(ex->toString().toStdString());
  delete ex;
}

void BetControllerLib::updateMarketBook() {
  std::list<QString> marketsToUpdate;

  m_marketsData.getMarketIdsToUpdate(marketsToUpdate);
  m_marketsData.increaseUpdateSlot();

  if (marketsToUpdate.size() > 0) {
    m_marketBookApi->getMarketBook(marketsToUpdate);
  }
}

void BetControllerLib::keepAliveTimeout() {
  qDebug() << "Sent keep alive...";
  m_keepAliveApi->sendKeepAlive();
}

void BetControllerLib::receivedEvents(std::list<BfEvent> newEvents) {
  qDebug() << "BetControllerLib::receivedEvents";
  // Get market catalogue for events not allready active
  m_lastReceivedEvents = newEvents;

  for (std::list<BfEvent>::iterator itNewEvent = m_lastReceivedEvents.begin();
       itNewEvent != m_lastReceivedEvents.end(); itNewEvent++) {
    if (m_marketsData.isEventAdded(itNewEvent->m_eventId)) {
      continue; // Try next
    }

    // Check if part of this unit
    bool ok = false;
    int eventIdInteger = itNewEvent->m_eventId.toInt(&ok);
    if (!ok) {
      continue;
    }
    if((eventIdInteger % m_config->getUnitCounts()) != m_config->getUnitIndex()) {
      continue;
    }


    // New event is not allready active, get market catalogue
    std::pair<BetfairMarketFilter, std::list<BfMarketProjection::Enum> > filterproj =
        BfFilterFactory::getMarketCatalogueFilter(itNewEvent->m_eventId);
    m_marketCatalogueApi->get(filterproj.first, filterproj.second);
  }
}

void BetControllerLib::receivedMarketCatalogue(QString eventId,
                                               std::list<BetfairMarket> markets) {
  // Find event from eventId
  for (std::list<BfEvent>::iterator itEvent = m_lastReceivedEvents.begin();
       itEvent != m_lastReceivedEvents.end(); itEvent++) {
    if (itEvent->m_eventId == eventId) {
      // Update competition if neccessary
      for (std::list<BetfairMarket>::iterator itMarket = markets.begin();
           itMarket != markets.end(); itMarket++) {
        if (itEvent->m_competition == BfCompetition::ALL ||
            itEvent->m_competition == BfCompetition::UNKOWN) {
          if (itMarket->m_competition != BfCompetition::ALL &&
              itMarket->m_competition != BfCompetition::UNKOWN) {
            itEvent->m_competition = itMarket->m_competition;
          }
        } else {
          break;
        }
      }

      // Try to add an event to a slot
      if (!m_eventStats.hasStoppedGettingEvent(eventId) &&
          m_marketsData.addEvent(*itEvent, markets)) {
        qDebug() << "Start getting event: " << eventId;
        m_eventStats.startGettingEvent(itEvent->m_eventId);
      }
      break;
    }
  }
}

void BetControllerLib::receivedMarketBookData(std::list<BetfairMarket> markets) {
  if (markets.size() > 0) {
    std::list< std::pair<BfEvent, std::list<BetfairMarket> > > *newData = m_marketsData.updateMarketBook(markets);

    if (newData != 0) {
      for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator newDataIt = newData->begin();
           newDataIt != newData->end(); newDataIt++) {
        QString eventId = newDataIt->first.m_eventId;
        m_eventStats.updateStats(eventId, newDataIt->second);

        // Choose bets to play
        std::map<QString, std::list<BfPlaceInstruction> > placeInstructions;
        m_betHandler.chooseBets(newDataIt->first, newDataIt->second, placeInstructions);
        if (placeInstructions.size() == 0) {
          manualPlaceBets(newDataIt->first, newDataIt->second, placeInstructions);
        }

        for(std::map<QString, std::list<BfPlaceInstruction> >::const_iterator itPI = placeInstructions.begin();
            itPI != placeInstructions.end(); itPI++) {
          m_placeOrdersApi->placeOrders(itPI->first, itPI->second);
        }

        if (m_config->logData()) {
          m_eventDataConsumer->push(newDataIt->first, newDataIt->second);
        }
      }
    } else {
      qDebug() << "BetControllerLib::receivedMarketBookData: newData null for some reason..";
    }
  }
}

void BetControllerLib::receivedPlaceOrdersRsp(BfPlaceExecutionReport placeExecutionReport) {
  m_betHandler.placeOrdersRsp(placeExecutionReport);
}

void BetControllerLib::receivedAccountDetails(BfAccountDetailsRsp accountDetailsRsp) {
  qDebug() << "BetControllerLib::receivedAccountDetails(";
  Q_UNUSED(accountDetailsRsp);
}

void BetControllerLib::receivedAccountFunds(BfAccountFundsRsp accountFundsRsp) {
  qDebug() << "BetControllerLib::receivedAccountFunds";
  m_accountsHandler.accountInfoReceived(accountFundsRsp);
}
