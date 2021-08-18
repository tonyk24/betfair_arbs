#ifndef BETFAIRLIB_H
#define BETFAIRLIB_H

#include <QString>
#include <QTimer>
#include "betlib_global.h"

#include "betfairapi/accountsapi.h"
#include "betfairapi/eventsapi.h"
#include "betfairapi/marketbookeapi.h"
#include "betfairapi/keepaliveapi.h"
#include "betfairapi/placeordersapi.h"

#include "bfenums/bfcompetition.h"

#include "bftypes/bfapingexception.h"
#include "bftypes/bfaccountdetailsrsp.h"
#include "bftypes/bfaccountfundsrsp.h"

#include "eventdataconsumer.h"
#include "betting/bethandler.h"
#include "betting/eventstats.h"
#include "betting/marketsdata.h"

#include "misc/config.h"

using namespace BfLib;

class BETLIBSHARED_EXPORT BetControllerLib : public QObject
{
  Q_OBJECT
public:
  BetControllerLib(QObject *parent, Config *config);
  ~BetControllerLib();

  void quit() {
    m_quit = true;
  }

  void sendListEvents() {
    m_debugMsgListEvents = true;
  }
  void sendListEventsDetailed(int slot) {
    m_debugMsgListEventsDetailed = true;
    m_debugMsgListeEventDetailsSlot = slot;
  }

  void sendListEventsBets(int slot, int index) {
    m_debugMsgListEventBets = true;
    m_debugMsgListeEventDetailsSlot = slot;
    m_debugMsgListeEventDetailsIndex = index;
  }

  void sendListEventsBets(int slot, int index, QString market) {
    m_debugMsgListEventBetsMarket = true;
    m_debugMsgListeEventDetailsSlot = slot;
    m_debugMsgListeEventDetailsIndex = index;
    m_debugMsgListeEventDetailsMarket = market;
  }

  void sendListAccount() {
    m_debugMsgListAccount = true;
  }
  void sendListEventDataConsumer() {
    m_debugMsgListEventDataConsumer = true;
  }
  void sendListConfig() {
    m_debugMsgListConfig = true;
  }

  void sendTakeBet(QString eventId,
                   qint64 selId,
                   BfSide::Enum side) {
    m_debugMsgTakeBet = true;
    m_debugMsgTakeBetEventId = eventId;
    m_debugMsgTakeBetSelId = selId;
    m_debugMsgTakeBetSide = side;
  }

  void manualPlaceBets(const BfEvent &event,
                       const std::list<BetfairMarket> &markets,
                       std::map<QString, std::list<BfPlaceInstruction> > &placeBets) {
    if (m_debugMsgTakeBet && m_debugMsgTakeBetEventId == event.m_eventId) {
      m_debugMsgTakeBet = false;

      for (std::list<BetfairMarket>::const_iterator itM = markets.begin();
           itM != markets.end(); itM++) {
        for (std::list<BetfairSelection>::const_iterator itSel = itM->m_selections.begin();
             itSel != itM->m_selections.end(); itSel++) {
          qDebug() << "eID= " << event.m_eventId
                   << "mID= " << itM->m_marketId
                   << " " << BfMarketStatus::toStr(itM->m_marketStatus)
                   << " " << QString::number(itSel->m_selectionId)
                   << " " << itSel->m_status;
          if (itSel->m_selectionId == m_debugMsgTakeBetSelId &&
              itM->m_marketStatus == BfMarketStatus::OPEN &&
              itSel->m_status == "ACTIVE") {

            double takePrice = -1.0;
            double takeSize = -1.0;

            if (m_debugMsgTakeBetSide == BfSide::BACK &&
                itSel->m_availableToBackPrice.size() > 0 &&
                itSel->m_availableToBackSize.size() > 0) {
              takePrice = itSel->m_availableToBackPrice[0];
              takeSize = 30;
            }
            if (m_debugMsgTakeBetSide == BfSide::LAY &&
                itSel->m_availableToLayPrice.size() > 0 &&
                itSel->m_availableToLaySize.size() > 0) {
              takePrice = itSel->m_availableToLayPrice[0];
              takeSize = 30;
            }

            if (takePrice > 0.0 && takeSize > 0.0) {
              BfPlaceInstruction bet1 = BfPlaceInstruction(BfOrderType::LIMIT,
                                                         m_debugMsgTakeBetSelId,
                                                           itSel->m_handicap,
                                                         m_debugMsgTakeBetSide,
                                                         BfLimitOrder(takePrice, takeSize, BfPersistenceType::LAPSE));
              placeBets[itM->m_marketId].push_back(bet1);
              emit debugMsg("Taking bets on mid= " + itM->m_marketId);
              return;
            }
          }
        }
      }

      emit debugMsg("Not taking bets...");
    }
  }

private:
  MarketBookApi *m_marketBookApi;
  EventsApi *m_eventsApi;
  KeepAliveApi *m_keepAliveApi;
  PlaceOrdersApi *m_placeOrdersApi;
  AccountsApi *m_accountsApi;
  MarketCatalogueApi *m_marketCatalogueApi;

  QTimer *m_marketDataUpdateTimer;

  QTimer *m_keepAliveTimer;

  Config *m_config;
  EventDataConsumer *m_eventDataConsumer;

  std::list<BfEvent> m_lastReceivedEvents;

  AccountsHandler m_accountsHandler;
  BetHandler m_betHandler;
  EventStats m_eventStats;
  MarketsData m_marketsData;

  // Send debug messages to listener
  bool m_quit;
  bool m_debugMsgListEvents;

  bool m_debugMsgListEventsDetailed;
  bool m_debugMsgListEventBets;
  bool m_debugMsgListEventBetsMarket;
  int m_debugMsgListeEventDetailsSlot;
  int m_debugMsgListeEventDetailsIndex;
  QString m_debugMsgListeEventDetailsMarket;

  bool m_debugMsgTakeBet;
  QString m_debugMsgTakeBetEventId;
  qint64 m_debugMsgTakeBetSelId;
  BfSide::Enum m_debugMsgTakeBetSide;

  bool m_debugMsgListAccount;
  bool m_debugMsgListEventDataConsumer;
  bool m_debugMsgListConfig;

public slots:
  void run();
  void aboutToQuitApp();

  void receivedEvents(std::list<BfEvent> events);
  void receivedMarketCatalogue(QString event, std::list<BetfairMarket> markets);
  void receivedMarketBookData(std::list<BetfairMarket> markets);
  void receivedPlaceOrdersRsp(BfPlaceExecutionReport placeExecutionReport);

  void receivedAccountDetails(BfAccountDetailsRsp accountDetailsRsp);
  void receivedAccountFunds(BfAccountFundsRsp accountFundsRsp);

  void errorOccurred(BfApiNgException *ex);
private slots:
  void updateMarketBook();
  void keepAliveTimeout();

  void threadError(QString errorno) {
    qWarning() << "Received thread error: " << errorno;
  }
  void threadMessage(QString msg) {
    qDebug() << "Received thread message: " << msg;
  }

signals:
  void valueChangedEvents(std::list<BfEvent> events);
  void valueChangedMarkets(QString event, std::list<BetfairMarket> markets);
  void valueChangedAccountFunds(BfAccountFundsRsp accountFundsRsp);
  void valueChangedAccountDetails(BfAccountDetailsRsp accountFundsRsp);
  void placeOrdersResponse(BfPlaceExecutionReport placeExecutionReport);

  void error(BfApiNgException *ex);

  void finished();

  // Debug output
  void debugMsg(QString msg);
};

#endif // BETFAIRLIB_H
