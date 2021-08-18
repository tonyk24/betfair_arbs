#ifndef SOCCERGAME_H
#define SOCCERGAME_H
#include <QObject>

#include "betfairapi/eventsapi.h"
#include "betfairapi/marketbookeapi.h"
#include "betfairapi/keepaliveapi.h"
#include "betfairapi/placeordersapi.h"
#include "betfairapi/listcurrentordersapi.h"
#include "betfairapi/cancelordersapi.h"
#include "bfenums/bfside.h"
#include "misc/config.h"

#include "betting/eventstats.h"
#include "arbcalculator.h"
#include "resmat.h"
#include "types/extbet.h"
#include "types/bfarbbet.h"

class SoccerGame: public QObject
{
  Q_OBJECT
public:
  SoccerGame(QObject *parent, Config *config, BfEvent bfEvent);
  ~SoccerGame();
  BfEvent m_bfEvent;

  void start()
  {
    emit resultMatrixUpdated(m_resultMatrixReal,
                             m_resultMatrixRealnSimulation,
                             m_resultMatrixSimulation,
                             m_resultMatrixLuckyBets);
  }

  void getMarketData();
  void getPlacedBets();
  void setBetSize(double betSize)
  {
    m_betSize = betSize;
  }

  double checkPlaceBetSimulatedSize(qint64 selectionId, BfSide::Enum side);
  void removePlacedBet(std::pair<BfPlaceExecutionReport,BfCurrentOrder>);
signals:
  marketsDataUpdated(std::list<BfLib::BetfairMarket> marketBook);
  resultMatrixUpdated(ResMat resmatReal,
                      ResMat resmatRealSim,
                      ResMat resmatSim,
                      ResMat resmatLuckyBets);
  totalGoalsUpdated(EventStats::TOTALGOALS_EQ, EventStats::TOTALGOALS_LE);

  // Placed bets
  placedBetsUpdated(std::list<std::pair<BfLib::BfPlaceExecutionReport,BfLib::BfCurrentOrder> >);

  arbBetsUpdate(std::list<BfArbBet>);
  arbBetsExtChanged(std::list<ExtBet> extBets);

  bfSimulationBetsUpdated(std::list<BfLib::BfPlaceInstruction>);
public slots:
  // From betfair api
  void receivedMarketCatalogue(QString event, std::list<BfLib::BetfairMarket> marketCatalogue);
  void receivedMarketBookData(std::list<BfLib::BetfairMarket> marketBook);
  void receivedPlaceOrdersRsp(BfLib::BfPlaceExecutionReport placeExecutionReport);
  void receivedListCurrentOrdersRsp(std::list<BfLib::BfCurrentOrder> currentOrders);

  // Placing bets and simulation
  void placeBetSimulated(QString marketId, qint64 selectionId,
                            double handicap, BfLib::BfSide::Enum side,
                            double takePrice, double takeSize);
  void placeBetSimulatedRemove(QString marketId, qint64 selectionId,
                            double handicap, BfLib::BfSide::Enum side);

  void placeBet(QString marketId, qint64 selectionId,
                double handicap, BfLib::BfSide::Enum side,
                double takePrice, double takeSize);
  void placeBet(QString marketId, BfLib::BfPlaceInstruction pi);

  // From Ext bets
  void placeExtBetSimulated(ExtBet);
  void placeExtBetSimulatedRemoved(ExtBet);
private slots:
  void errorOccurred(BfLib::BfApiNgException *ex);

private:
  MarketCatalogueApi *m_marketCatalogueApi;
  MarketBookApi *m_marketBookApi;

  PlaceOrdersApi *m_placeOrdersApi;
  ListCurrentOrdersApi *m_listCurrentOrdersApi;
  CancelOrdersApi *m_cancelOrdersApi;
  Config *m_config;

  std::list<BetfairMarket> m_currentMarketCatalogue;
  std::list<BetfairMarket> m_currentMarketBook;
  void sortmarkets(std::list<BetfairMarket>&);


  double m_betSize;

  EventStats *m_eventStats;
  ArbCalculator m_arbCalculator;
  std::list<BfArbBet> m_currentArbBets;
  void updateCurrentArbBets(const std::map<QString, std::list<BfPlaceInstruction> > &placeBets);

  std::list<std::pair<BfPlaceExecutionReport,BfCurrentOrder> > m_placedBets;
  std::list<BfPlaceInstruction> m_simulatedBets;

  std::list<ExtBet> m_extSimulatedBets;

  // Result matrix
  ResMat m_resultMatrixReal;
  ResMat m_resultMatrixRealnSimulation;
  ResMat m_resultMatrixSimulation;
  ResMat m_resultMatrixLuckyBets;
  void updateResultMatrix();
};

#endif // SOCCERGAME_H
