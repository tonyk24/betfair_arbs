#include <list>
#include "soccergame.h"

#include "betfairapi/marketbookeapi.h"
#include "betfairapi/keepaliveapi.h"
#include "betfairapi/cancelordersapi.h"
#include "factory/bffilterfactory.h"



SoccerGame::SoccerGame(QObject *parent, Config *config,BfEvent bfEvent)
  : m_bfEvent(bfEvent),
    m_config(config)
{
  m_marketCatalogueApi = new MarketCatalogueApi(0, m_config->getBfConfig());
  m_marketBookApi = new MarketBookApi(0, m_config->getBfConfig());
  m_placeOrdersApi = new PlaceOrdersApi(0, m_config->getBfConfig());
  m_listCurrentOrdersApi = new ListCurrentOrdersApi(0, m_config->getBfConfig());
  m_cancelOrdersApi = new CancelOrdersApi(0, m_config->getBfConfig());
  m_eventStats = new EventStats();


  QObject::connect(m_marketCatalogueApi, SIGNAL(valueChanged(QString, std::list<BfLib::BetfairMarket>)),
                   this, SLOT(receivedMarketCatalogue(QString, std::list<BfLib::BetfairMarket>)));
  QObject::connect(m_marketBookApi, SIGNAL(valueChanged(std::list<BfLib::BetfairMarket>)),
                   this, SLOT(receivedMarketBookData(std::list<BfLib::BetfairMarket>)));
  QObject::connect(m_placeOrdersApi, SIGNAL(placeOrdersResponse(BfLib::BfPlaceExecutionReport)),
                   this, SLOT(receivedPlaceOrdersRsp(BfLib::BfPlaceExecutionReport)));
  QObject::connect(m_listCurrentOrdersApi, SIGNAL(listCurrentOrdersResponse(std::list<BfLib::BfCurrentOrder>)),
                   this, SLOT(receivedListCurrentOrdersRsp(std::list<BfLib::BfCurrentOrder>)));


  // ERRORS
  QObject::connect(m_marketCatalogueApi, SIGNAL(error(BfLib::BfApiNgException*)),
                   this, SLOT(errorOccurred(BfLib::BfApiNgException*)));
  QObject::connect(m_marketBookApi, SIGNAL(error(BfLib::BfApiNgException*)),
                   this, SLOT(errorOccurred(BfLib::BfApiNgException*)));
  QObject::connect(m_placeOrdersApi, SIGNAL(error(BfLib::BfApiNgException*)),
                   this, SLOT(errorOccurred(BfLib::BfApiNgException*)));
  QObject::connect(m_listCurrentOrdersApi, SIGNAL(error(BfLib::BfApiNgException*)),
                   this, SLOT(errorOccurred(BfLib::BfApiNgException*)));


}

SoccerGame::~SoccerGame()
{
  delete m_marketBookApi;

  delete m_placeOrdersApi;
  delete m_listCurrentOrdersApi;
  delete m_cancelOrdersApi;
}

void SoccerGame::getMarketData()
{
  // New event is not allready active, get market catalogue
  std::pair<BetfairMarketFilter, std::list<BfMarketProjection::Enum> > filterproj =
      BfFilterFactory::getMarketCatalogueFilter(m_bfEvent.m_eventId);
  m_marketCatalogueApi->get(filterproj.first, filterproj.second);
}

void SoccerGame::getPlacedBets()
{
  std::list<QString> marketIds;
  for (std::list<BetfairMarket>::iterator it = m_currentMarketBook.begin();
       it != m_currentMarketBook.end(); it++)
    marketIds.push_back(it->m_marketId);

  if (marketIds.size() > 0)
    m_listCurrentOrdersApi->listCurrentOrders(marketIds);
}

void SoccerGame::removePlacedBet(std::pair<BfPlaceExecutionReport, BfCurrentOrder> placedBet)
{
  for (std::list<std::pair<BfPlaceExecutionReport,BfCurrentOrder> >::iterator it = m_placedBets.begin();
       it != m_placedBets.end();)
  {
    if (placedBet.second.m_betId == "" &&
        placedBet.second.m_marketId == it->first.m_marketId)
      it = m_placedBets.erase(it);
    else if (placedBet.second.m_betId == it->second.m_betId &&
             placedBet.second.m_marketId == it->second.m_marketId)
    {
      it = m_placedBets.erase(it);
      BfCancelInstruction bfCancelInstruction;
      bfCancelInstruction.m_betId = it->second.m_betId;
      std::list<BfCancelInstruction> bfcis;
      bfcis.push_back(bfCancelInstruction);
      m_cancelOrdersApi->cancelOrders(it->second.m_marketId,bfcis);
    }
    else
      it++;
  }
  emit placedBetsUpdated(m_placedBets);

}

void SoccerGame::placeBet(QString marketId, qint64 selectionId,
                          double handicap, BfSide::Enum side,
                          double takePrice, double takeSize)
{
  BfPlaceInstruction bet(BfOrderType::LIMIT,
                         selectionId,
                         handicap,
                         side,
                         BfLimitOrder(takePrice, takeSize, BfPersistenceType::LAPSE));

  std::list<BfPlaceInstruction> bets;
  bets.push_back(bet);
  m_placeOrdersApi->placeOrders(marketId, bets);
}

void SoccerGame::placeBet(QString marketId, BfPlaceInstruction pi)
{
  std::list<BfPlaceInstruction> bets;
  bets.push_back(pi);
  m_placeOrdersApi->placeOrders(marketId, bets);
}

void SoccerGame::placeBetSimulated(QString marketId, qint64 selectionId,
                                   double handicap, BfSide::Enum side,
                                   double takePrice, double takeSize)
{
  BfPlaceInstruction bet(BfOrderType::LIMIT,
                         selectionId,
                         handicap,
                         side,
                         BfLimitOrder(takePrice, takeSize, BfPersistenceType::LAPSE));

  m_simulatedBets.push_back(bet);

  updateResultMatrix();
}

void SoccerGame::placeBetSimulatedRemove(QString marketId, qint64 selectionId,
                                         double handicap, BfSide::Enum side)
{
  for(std::list<BfPlaceInstruction>::iterator it = m_simulatedBets.begin();
      it != m_simulatedBets.end(); it++)
  {
    if (it->m_selectionId == selectionId &&
        it->m_handicap == handicap &&
        it->m_side == side)
    {
      m_simulatedBets.erase(it);
      break;
    }
  }

  updateResultMatrix();
}



void SoccerGame::placeExtBetSimulated(ExtBet extBet)
{
  placeExtBetSimulatedRemoved(extBet);

  m_extSimulatedBets.push_back(extBet);

  updateResultMatrix();
}

void SoccerGame::placeExtBetSimulatedRemoved(ExtBet extBet)
{
  for (std::list<ExtBet>::iterator it = m_extSimulatedBets.begin();
       it != m_extSimulatedBets.end(); it++)
  {
    if (it->m_name == extBet.m_name &&
        it->m_type == extBet.m_type)
    {
      m_extSimulatedBets.erase(it);
      break;
    }
  }

  updateResultMatrix();
}

double SoccerGame::checkPlaceBetSimulatedSize(qint64 selectionId, BfSide::Enum side)
{
  for(std::list<BfPlaceInstruction>::iterator it = m_simulatedBets.begin();
      it != m_simulatedBets.end(); it++)
  {
    if (it->m_selectionId == selectionId &&
        it->m_side == side)
    {
      return it->m_limitOrder.m_size;
    }
  }
  return 0.0;
}

void SoccerGame::receivedMarketCatalogue(QString eventId,
                                         std::list<BetfairMarket> marketCatalogue) {
  //qDebug() << "Received market catalogue eventid=" << eventId
  //         << ", markets=" << QString::number(marketCatalogue.size());


  m_currentMarketCatalogue = marketCatalogue;
  for (std::list<BetfairMarket>::iterator itMarket = marketCatalogue.begin();
       itMarket != marketCatalogue.end(); itMarket++) {
    for (std::list<BetfairSelection>::iterator itSel = itMarket->m_selections.begin();
         itSel != itMarket->m_selections.end(); itSel++)
    {
      //qDebug() << "name= " << itMarket->m_marketName << "mid= " << itMarket->m_marketId;
      //qDebug() << "name= " << itSel->m_selectionName << "sid= " << itSel->m_selectionId;
    }

  }

  std::list<QString> marketsToUpdate;

  for (std::list<BetfairMarket>::iterator itMarket = marketCatalogue.begin();
       itMarket != marketCatalogue.end(); itMarket++) {
    marketsToUpdate.push_back(itMarket->m_marketId);
  }

  if (marketsToUpdate.size() > 0) {
    m_marketBookApi->getMarketBook(marketsToUpdate);
  }
}

void SoccerGame::receivedMarketBookData(std::list<BetfairMarket> marketBook) {


  m_currentMarketBook = marketBook;
  for (std::list<BetfairMarket>::iterator itMarket = marketBook.begin();
       itMarket != marketBook.end(); itMarket++) {
    for (std::list<BetfairSelection>::iterator itSel = itMarket->m_selections.begin();
         itSel != itMarket->m_selections.end(); itSel++)
    {
      //qDebug() << "name= " << itMarket->m_marketName << "mid= " << itMarket->m_marketId;
      //qDebug() << "name= " << itSel->m_selectionName << "sid= " << itSel->m_selectionId;
    }
  }

  // Update marketname & selection name in marketbook
  for (std::list<BetfairMarket>::iterator itMarketBook =  m_currentMarketBook.begin();
       itMarketBook != m_currentMarketBook.end(); itMarketBook++)
  {
    for (std::list<BetfairMarket>::iterator itMarketCat =  m_currentMarketCatalogue.begin();
         itMarketCat != m_currentMarketCatalogue.end(); itMarketCat++)
    {
      if (itMarketCat->m_marketId == itMarketBook->m_marketId)
      {
        for(std::list<BetfairSelection>::iterator itSelBook = itMarketBook->m_selections.begin();
            itSelBook != itMarketBook->m_selections.end(); itSelBook++)
        {
          for(std::list<BetfairSelection>::iterator itSelCatalogue = itMarketCat->m_selections.begin();
              itSelCatalogue != itMarketCat->m_selections.end(); itSelCatalogue++)
          {
            if (itSelBook->m_selectionId == itSelCatalogue->m_selectionId)
            {
              itSelBook->m_selectionName = itSelCatalogue->m_selectionName;
            }
          }
        }
        itMarketBook->m_marketName = itMarketCat->m_marketName;
      }
    }
  }

  sortmarkets(m_currentMarketCatalogue);
  sortmarkets(m_currentMarketBook);
  emit marketsDataUpdated(m_currentMarketBook);

  m_eventStats->updateStats(m_bfEvent.m_eventId,m_currentMarketBook);

  emit totalGoalsUpdated(m_eventStats->getTotalGoalsEquals(m_bfEvent.m_eventId),
                         m_eventStats->getTotalGoalsLessEquals(m_bfEvent.m_eventId));

  // Betfair arb bets updated
  m_currentArbBets.clear();
  m_arbCalculator.chooseBets(m_bfEvent, m_currentMarketBook,m_currentArbBets, m_betSize, m_eventStats);
  //updateCurrentArbBets(placeBets);
  emit arbBetsUpdate(m_currentArbBets);
  updateResultMatrix();
}

void SoccerGame::receivedPlaceOrdersRsp(BfPlaceExecutionReport placeExecutionReport) {
  qDebug() <<"placeOrdersRsp: " << placeExecutionReport.toStr();

  m_placedBets.push_back(std::make_pair(placeExecutionReport, BfCurrentOrder()));

  emit placedBetsUpdated(m_placedBets);
  updateResultMatrix();
}

void SoccerGame::receivedListCurrentOrdersRsp(std::list<BfCurrentOrder> currentOrders)
{
  //qDebug() << "receivedListCurrentOrdersRsp().." << currentOrders.size();

  for (std::list<BfCurrentOrder>::iterator it = currentOrders.begin();
       it != currentOrders.end(); it++)
  {
    bool found = false;

    for (std::list<std::pair<BfPlaceExecutionReport,BfCurrentOrder> >::iterator cit = m_placedBets.begin();
         cit != m_placedBets.end(); cit++)
    {
      if (cit->second.m_betId == it->m_betId)
      {
        cit->second = *it;
        found = true;
        break;
      }
    }

    if (!found)
      m_placedBets.push_back(std::make_pair(BfPlaceExecutionReport(), *it));
  }

  emit placedBetsUpdated(m_placedBets);

  updateResultMatrix();
}

void SoccerGame::errorOccurred(BfApiNgException *ex) {
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



bool compFirst(const BetfairMarket & a, const BetfairMarket & b) {
  int pointA = 0;
  int pointB = 0;
  if (a.m_marketName == "Match Odds")
    pointA = 0;
  else if (a.m_marketName == "Over/Under 0.5 Goals")
    pointA = 1;
  else if (a.m_marketName == "Over/Under 1.5 Goals")
    pointA = 2;
  else if (a.m_marketName == "Over/Under 2.5 Goals")
    pointA = 3;
  else if (a.m_marketName == "Over/Under 3.5 Goals")
    pointA = 4;
  else if (a.m_marketName == "Over/Under 4.5 Goals")
    pointA = 5;
  else if (a.m_marketName == "Over/Under 5.5 Goals")
    pointA = 6;
  else if (a.m_marketName == "Over/Under 6.5 Goals")
    pointA = 7;
  else if (a.m_marketName == "Over/Under 7.5 Goals")
    pointA = 8;
  else if (a.m_marketName == "Over/Under 8.5 Goals")
    pointA = 9;
  else if (a.m_marketName == "Correct Score")
    pointA = 10;
  else
    pointA = 11;

  if (b.m_marketName == "Match Odds")
    pointB = 0;
  else if (b.m_marketName == "Over/Under 0.5 Goals")
    pointB = 1;
  else if (b.m_marketName == "Over/Under 1.5 Goals")
    pointB = 2;
  else if (b.m_marketName == "Over/Under 2.5 Goals")
    pointB = 3;
  else if (b.m_marketName == "Over/Under 3.5 Goals")
    pointB = 4;
  else if (b.m_marketName == "Over/Under 4.5 Goals")
    pointB = 5;
  else if (b.m_marketName == "Over/Under 5.5 Goals")
    pointB = 6;
  else if (b.m_marketName == "Over/Under 6.5 Goals")
    pointB = 7;
  else if (b.m_marketName == "Over/Under 7.5 Goals")
    pointB = 8;
  else if (b.m_marketName == "Over/Under 8.5 Goals")
    pointB = 9;
  else if (b.m_marketName == "Correct Score")
    pointB = 10;
  else
    pointB = 11;
  return pointA < pointB;
}

void SoccerGame::sortmarkets(std::list<BetfairMarket> &list)
{
  list.sort(compFirst);
}

void SoccerGame::updateResultMatrix()
{
  m_resultMatrixReal.reset();
  m_resultMatrixReal.updateResMatPlacedBets(m_bfEvent,
                                            m_currentMarketCatalogue,
                                            m_placedBets);
  m_resultMatrixRealnSimulation.reset();
  m_resultMatrixRealnSimulation.updateResMatPlacedBets(m_bfEvent,
                                                       m_currentMarketCatalogue,
                                                       m_placedBets);
  m_resultMatrixRealnSimulation.updateResMatSimulationBets(m_bfEvent,
                                                           m_currentMarketCatalogue,
                                                           m_simulatedBets,
                                                           m_extSimulatedBets);
  m_resultMatrixSimulation.reset();
  m_resultMatrixSimulation.updateResMatSimulationBets(m_bfEvent,
                                                      m_currentMarketCatalogue,
                                                      m_simulatedBets,
                                                      m_extSimulatedBets);

  m_resultMatrixLuckyBets.reset();
  m_resultMatrixLuckyBets.updateResMatLucky(m_bfEvent,
                                            m_currentArbBets);

  emit resultMatrixUpdated(m_resultMatrixReal,
                           m_resultMatrixRealnSimulation,
                           m_resultMatrixSimulation,
                           m_resultMatrixLuckyBets);
}

void SoccerGame::updateCurrentArbBets(const std::map<QString, std::list<BfPlaceInstruction> > &placeBets)
{
  /*
  m_currentArbBets.clear();
  for (std::map<QString, std::list<BfPlaceInstruction> >::const_iterator itMap = placeBets.begin();
       itMap != placeBets.end(); itMap++)
  {
    for (std::list<BfPlaceInstruction>::const_iterator itPI = itMap->second.begin();
         itPI != itMap->second.end(); itPI++)
    {
      for (std::list<BetfairMarket>::iterator itMarketBook =  m_currentMarketBook.begin();
           itMarketBook != m_currentMarketBook.end(); itMarketBook++)
      {
        for(std::list<BetfairSelection>::iterator itSelBook = itMarketBook->m_selections.begin();
            itSelBook != itMarketBook->m_selections.end(); itSelBook++)
        {
          if (itMap->first == itMarketBook->m_marketId &&
              itPI->m_selectionId == itSelBook->m_selectionId)
          {
            m_currentArbBets.push_back(BfArbBet(m_currentArbBetId,*itMarketBook, *itSelBook, *itPI));
          }
        }
      }
    }
    m_currentArbBetId++;
  }
  */
}
