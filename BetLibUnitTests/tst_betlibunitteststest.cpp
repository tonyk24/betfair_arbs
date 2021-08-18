#define QT_NO_DEBUG_OUTPUT 1

#include <QString>
#include <QtTest>

#include "betting/bethandler.h"
#include "betting/betstatistics.h"
#include "betting/accountshandler.h"
#include "betting/eventstats.h"

#include "misc/config.h"

class BetLibUnitTestsTest : public QObject
{
  Q_OBJECT

public:
  BetLibUnitTestsTest();

  std::list<TwoCombination::Type> m_twoCombBackBackList;
  std::list<TwoCombination::Type> m_twoCombBackLayList;
  std::list<TwoCombination::Type> m_twoCombLayLayList;

  Config m_configUT;

  void initAccountsHandler(AccountsHandler &ah,
                           double wallet) {

    BfAccountFundsRsp afrsp;
    ah.requestSent();
    afrsp.m_availableToBetBalance = wallet;
    ah.accountInfoReceived(afrsp);
  }

  void setZeroTotalGoals(QString eventId, EventStats &es) {
    BfEvent event(eventId, "dummyEventName", "dummyLocale", "dummyTimeZone",
                QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1("1.120193194", "Over/Under 0.5 Goals", 0.0);
    BetfairSelection sel1(1222347, "Under 0.5 Goals");
    market1.m_selections.push_back(sel1);
    market1.m_marketStatus = BfMarketStatus::OPEN;

    BetfairMarket market2("1.120193195", "Over/Under 1.5 Goals", 0.0);
    market2.m_marketStatus = BfMarketStatus::SUSPENDED;

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    es.updateStats(event.m_eventId,markets);
  }

private Q_SLOTS:
  void initTestCase();
  void cleanupTestCase();

  // TotalGoals counter
  void tc_totalGoalsCounter();

  // Bethandler -
  void tc_findBackLayPositiveOutcome();

  // BetHandler back/back
  void noFound_NoTake_back_back();
  void found_OverMaxPlacement_NoTake_back_back();
  void found_UnderMaxPlacement_Take_back_back();
  void found_ImpliedMaxExposure1_Take_back_back();
  void found_ImpliedMaxExposure2_Take_back_back();

  void take_and_NoTake_back_back();
  void take_and_take_back_back();

  // BetHandler back/lay
  void noFound_NoTake_back_to_lay();
  void found_underMaxExposure_Take_back_to_lay();
  void found_ImpliedMaxExposure1_Take_back_to_lay();
  void found_ImpliedMaxExposure2_Take_back_to_lay();
  void found_TakeSize1ToSmall_Take_back_to_lay();
  void found_TakeSize2ToSmall_Take_back_to_lay();
  void found_TakeSize1AndSize2ToSmall_NoTake_back_to_lay();

  // BetHandler lay/lay
  void noFound_NoTake_lay_to_lay();
  void found_maxExposureToSmall_NoTake_lay_to_lay();
  void found_underMaxExposure_Take_lay_to_lay();
  void found_ImpliedMaxExposure1_Take_lay_to_lay();
  void found_ImpliedMaxExposure2_Take_lay_to_lay();

  void tc_BetStatistics_hasActiveCombinations_2CombBothSuccssfull();
  void tc_BetStatistics_hasActiveCombinations_2CombPartlySuccssfull();

  void tc_EventDataConsumer_loggingevent_finnish();
  void tc_EventDataConsumer_loggingevent_abortEvent();
  void tc_EventDataConsumer_nologgingevent_abortEvent();
};

BetLibUnitTestsTest::BetLibUnitTestsTest() :
  m_configUT(false)
{
  m_configUT.setDoBetting(true);
  m_twoCombBackBackList.push_back(TwoCombination::BACKNG_NO_GOAL_to_BACKOU05_OVER);
  m_twoCombBackBackList.push_back(TwoCombination::BACKCS_0_0_to_BACKOU05_OVER);
  m_twoCombBackBackList.push_back(TwoCombination::BACKOU05_UNDER_to_BACKTG_1_OR_MORE);
  m_twoCombBackBackList.push_back(TwoCombination::BACKOU15_UNDER_to_BACKTG_2_OR_MORE);
  m_twoCombBackBackList.push_back(TwoCombination::BACKOU25_UNDER_to_BACKTG_3_OR_MORE);
  m_twoCombBackBackList.push_back(TwoCombination::BACKOU35_UNDER_to_BACKTG_4_OR_MORE);
  m_twoCombBackBackList.push_back(TwoCombination::BACKOU45_UNDER_to_BACKTG_5_OR_MORE);

  m_twoCombBackLayList.push_back(TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER);
  m_twoCombBackLayList.push_back(TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER);
  m_twoCombBackLayList.push_back(TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE);
  m_twoCombBackLayList.push_back(TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE);
  m_twoCombBackLayList.push_back(TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE);
  m_twoCombBackLayList.push_back(TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE);
  m_twoCombBackLayList.push_back(TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE);

  m_twoCombBackLayList.push_back(TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL);
  m_twoCombBackLayList.push_back(TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0);
  m_twoCombBackLayList.push_back(TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER);
  m_twoCombBackLayList.push_back(TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER);
  m_twoCombBackLayList.push_back(TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER);
  m_twoCombBackLayList.push_back(TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER);
  m_twoCombBackLayList.push_back(TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER);

  m_twoCombBackLayList.push_back(TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0);
  m_twoCombBackLayList.push_back(TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL);

  m_twoCombLayLayList.push_back(TwoCombination::LAYNG_NO_GOAL_to_LAYOU05_OVER);
  m_twoCombLayLayList.push_back(TwoCombination::LAYCS_0_0_to_LAYOU05_OVER);
  m_twoCombLayLayList.push_back(TwoCombination::LAYO05_UNDER_to_LAY_TG_1_OR_MORE);
  m_twoCombLayLayList.push_back(TwoCombination::LAYO15_UNDER_to_LAY_TG_2_OR_MORE);
  m_twoCombLayLayList.push_back(TwoCombination::LAYO25_UNDER_to_LAY_TG_3_OR_MORE);
  m_twoCombLayLayList.push_back(TwoCombination::LAYO35_UNDER_to_LAY_TG_4_OR_MORE);
  m_twoCombLayLayList.push_back(TwoCombination::LAYO45_UNDER_to_LAY_TG_5_OR_MORE);
}

void BetLibUnitTestsTest::initTestCase()
{
}

void BetLibUnitTestsTest::cleanupTestCase()
{
}


void BetLibUnitTestsTest::tc_totalGoalsCounter() {
  EventStats es;

  BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
              QDateTime::currentDateTimeUtc().toString());

  std::list<BetfairMarket> markets;

  QVERIFY(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_UNKOWN);

  es.updateStats(event.m_eventId, markets);
  QVERIFY(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_UNKOWN);

  BetfairMarket market05("1.120193194", "Over/Under 0.5 Goals", 0.0);
  BetfairMarket market15("1.120193194", "Over/Under 1.5 Goals", 0.0);
  BetfairMarket market25("1.120193194", "Over/Under 2.5 Goals", 0.0);
  BetfairMarket market35("1.120193194", "Over/Under 3.5 Goals", 0.0);
  BetfairMarket market45("1.120193194", "Over/Under 4.5 Goals", 0.0);
  BetfairMarket market55("1.120193194", "Over/Under 5.5 Goals", 0.0);
  BetfairMarket market65("1.120193194", "Over/Under 6.5 Goals", 0.0);
  BetfairMarket market75("1.120193194", "Over/Under 7.5 Goals", 0.0);
  BetfairMarket market85("1.120193194", "Over/Under 8.5 Goals", 0.0);
  BetfairMarket market95("1.120193194", "Over/Under 9.5 Goals", 0.0);

  market15.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market15);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_UNKOWN, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // Total Goals = 0
  market05.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_0, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());


  // Total Goals = 0
  market05.m_marketStatus = BfMarketStatus::OPEN;
  market15.m_marketStatus = BfMarketStatus::OPEN;
  market25.m_marketStatus = BfMarketStatus::OPEN;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_0, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // Total Goals = 0
  market05.m_marketStatus = BfMarketStatus::OPEN;
  market15.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_0, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());


  // OU05 Closed - 1 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::OPEN;
  market25.m_marketStatus = BfMarketStatus::OPEN;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_1, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU05 Closed - 1 TG
  market05.m_marketStatus = BfMarketStatus::SUSPENDED;
  market15.m_marketStatus = BfMarketStatus::OPEN;
  market25.m_marketStatus = BfMarketStatus::OPEN;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_1, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU05 Closed - 1 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::INACTIVE;
  market25.m_marketStatus = BfMarketStatus::INACTIVE;
  market35.m_marketStatus = BfMarketStatus::INACTIVE;
  market45.m_marketStatus = BfMarketStatus::INACTIVE;
  market55.m_marketStatus = BfMarketStatus::INACTIVE;
  market65.m_marketStatus = BfMarketStatus::INACTIVE;
  market75.m_marketStatus = BfMarketStatus::INACTIVE;
  market85.m_marketStatus = BfMarketStatus::INACTIVE;
  market95.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_1, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU05 Closed - 1 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_1, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU05 Closed - 1 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::OPEN;
  market25.m_marketStatus = BfMarketStatus::OPEN;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_1, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU15 Closed - 2 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::OPEN;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_2, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU15 Closed - 2 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_2, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU15 Closed - 2 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::SUSPENDED;
  market25.m_marketStatus = BfMarketStatus::OPEN;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_2, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU15 Closed - 2 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::INACTIVE;
  market35.m_marketStatus = BfMarketStatus::INACTIVE;
  market45.m_marketStatus = BfMarketStatus::INACTIVE;
  market55.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_2, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU25 Closed - 3 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_3, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU25 Closed - 3 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::INACTIVE;
  market45.m_marketStatus = BfMarketStatus::INACTIVE;
  market55.m_marketStatus = BfMarketStatus::INACTIVE;
  market65.m_marketStatus = BfMarketStatus::INACTIVE;
  market75.m_marketStatus = BfMarketStatus::INACTIVE;
  market85.m_marketStatus = BfMarketStatus::INACTIVE;
  market95.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_3, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU25 Closed - 3 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::SUSPENDED;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_3, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU25 Closed - 3 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_3, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU35 Closed - 4 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_4, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU35 Closed - 4 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::SUSPENDED;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_4, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU35 Closed - 4 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::INACTIVE;
  market55.m_marketStatus = BfMarketStatus::INACTIVE;
  market65.m_marketStatus = BfMarketStatus::INACTIVE;
  market75.m_marketStatus = BfMarketStatus::INACTIVE;
  market85.m_marketStatus = BfMarketStatus::INACTIVE;
  market95.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_4, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU35 Closed - 4 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_4, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU45 Closed - 5 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_5, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU45 Closed - 5 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::INACTIVE;
  market65.m_marketStatus = BfMarketStatus::INACTIVE;
  market75.m_marketStatus = BfMarketStatus::INACTIVE;
  market85.m_marketStatus = BfMarketStatus::INACTIVE;
  market95.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_5, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU45 Closed - 5 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::SUSPENDED;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_5, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU45 Closed - 5 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_5, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU55 Closed - 6 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_6, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU55 Closed - 6 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::INACTIVE;
  market75.m_marketStatus = BfMarketStatus::INACTIVE;
  market85.m_marketStatus = BfMarketStatus::INACTIVE;
  market95.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_6, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU55 Closed - 6 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::SUSPENDED;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_6, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU55 Closed - 6 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_6, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU65 Closed - 7 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_7, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU65 Closed - 7 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::INACTIVE;
  market85.m_marketStatus = BfMarketStatus::INACTIVE;
  market95.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_7, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU65 Closed - 7 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::SUSPENDED;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_7, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU65 Closed - 7 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_7, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU75 Closed - 8 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::CLOSED;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_8, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU75 Closed - 8 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::CLOSED;
  market85.m_marketStatus = BfMarketStatus::INACTIVE;
  market95.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_8, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU75 Closed - 8 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::SUSPENDED;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_8, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU75 Closed - 8 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::CLOSED;
  market85.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_8, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU85 Closed - 9 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::CLOSED;
  market85.m_marketStatus = BfMarketStatus::CLOSED;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_9, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU85 Closed - 9 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::CLOSED;
  market85.m_marketStatus = BfMarketStatus::SUSPENDED;
  market95.m_marketStatus = BfMarketStatus::OPEN;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_9, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());

  // OU85 Closed - 9 TG
  market05.m_marketStatus = BfMarketStatus::CLOSED;
  market15.m_marketStatus = BfMarketStatus::CLOSED;
  market25.m_marketStatus = BfMarketStatus::CLOSED;
  market35.m_marketStatus = BfMarketStatus::CLOSED;
  market45.m_marketStatus = BfMarketStatus::CLOSED;
  market55.m_marketStatus = BfMarketStatus::CLOSED;
  market65.m_marketStatus = BfMarketStatus::CLOSED;
  market75.m_marketStatus = BfMarketStatus::CLOSED;
  market85.m_marketStatus = BfMarketStatus::CLOSED;
  market95.m_marketStatus = BfMarketStatus::INACTIVE;
  markets.clear();
  markets.push_back(market05);
  markets.push_back(market15);
  markets.push_back(market25);
  markets.push_back(market35);
  markets.push_back(market45);
  markets.push_back(market55);
  markets.push_back(market65);
  markets.push_back(market75);
  markets.push_back(market85);
  markets.push_back(market95);
  es.updateStats(event.m_eventId, markets);
  QVERIFY2(es.getTotalGoalsEquals(event.m_eventId) == EventStats::TGEQ_9, QString::number(es.getTotalGoalsEquals(event.m_eventId)).toStdString().c_str());
}

void BetLibUnitTestsTest::tc_findBackLayPositiveOutcome() {
  AccountsHandler ah(0, 125.0);
  EventStats es;
  setZeroTotalGoals("27517556", es);
  initAccountsHandler(ah, 350.0);
  BetHandler bh(0, &ah, &es, &m_configUT);
  // { "Correct Score" , "0 - 0" } { "Over/Under 0.5 Goals" , "Under 0.5 Goals" }
  // (price=  38 , size=  207.88 ) ( (price=  13 , size=  130.06 ) (
  bh.findBackLayPositiveOutcome(1/38.0, 1.0-1/13,
                                38.0, 207.88,
                                13, 130.06);
}

void BetLibUnitTestsTest::noFound_NoTake_back_back() {
  QVERIFY(m_twoCombBackBackList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackBackList.begin();
       it != m_twoCombBackBackList.end(); it++) {
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_to_BACKOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_BACKOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_BACKTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_UNDER_to_BACKTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221385;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_UNDER_to_BACKTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47972;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_UNDER_to_BACKTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222344;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_UNDER_to_BACKTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222347;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }

    AccountsHandler ah(0, 125.0);
    initAccountsHandler(ah, 350.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(1.99);
    sel1.m_availableToBackSize.push_back(1643.0);
    sel1.m_availableToLayPrice.push_back(2.02);
    sel1.m_availableToLaySize.push_back(849.19);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.52);
    sel2.m_availableToBackSize.push_back(24226);
    sel2.m_availableToLayPrice.push_back(2.6);
    sel2.m_availableToLaySize.push_back(297);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;


    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 0, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());
  }
}

void BetLibUnitTestsTest::found_OverMaxPlacement_NoTake_back_back() {
  QVERIFY(m_twoCombBackBackList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackBackList.begin();
       it != m_twoCombBackBackList.end(); it++) {
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_to_BACKOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_BACKOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_BACKTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_UNDER_to_BACKTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221385;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_UNDER_to_BACKTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47972;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_UNDER_to_BACKTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222344;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_UNDER_to_BACKTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222347;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }
    AccountsHandler ah(0, 30.0);
    initAccountsHandler(ah, 350.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(1.99);
    sel1.m_availableToBackSize.push_back(1643.0);
    sel1.m_availableToLayPrice.push_back(2.02);
    sel1.m_availableToLaySize.push_back(849.19);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(5);
    sel2.m_availableToBackSize.push_back(24226);
    sel2.m_availableToLayPrice.push_back(2.6);
    sel2.m_availableToLaySize.push_back(297);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;


    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 0, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());
  }
}

void BetLibUnitTestsTest::found_UnderMaxPlacement_Take_back_back() {
  QVERIFY(m_twoCombBackBackList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackBackList.begin();
       it != m_twoCombBackBackList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_to_BACKOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_BACKOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_BACKTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_UNDER_to_BACKTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221385;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_UNDER_to_BACKTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47972;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_UNDER_to_BACKTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222344;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_UNDER_to_BACKTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222347;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }
    AccountsHandler ah(0, 125.0);
    initAccountsHandler(ah, 350.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(1.99);
    sel1.m_availableToBackSize.push_back(1643.0);
    sel1.m_availableToLayPrice.push_back(2.02);
    sel1.m_availableToLaySize.push_back(849.19);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(5);
    sel2.m_availableToBackSize.push_back(24226);
    sel2.m_availableToLayPrice.push_back(2.6);
    sel2.m_availableToLaySize.push_back(297);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;


    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 1.99, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(std::fabs(placeBets[market1.m_marketId].front().m_limitOrder.m_size-89.4134) < 0.1, "size");



    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 5.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(std::fabs(placeBets[market2.m_marketId].front().m_limitOrder.m_size-35.5866) < 0.1, "size");
  }
}

void BetLibUnitTestsTest::found_ImpliedMaxExposure1_Take_back_back() {
  QVERIFY(m_twoCombBackBackList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackBackList.begin();
       it != m_twoCombBackBackList.end(); it++) {
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    double selHandicap1 = 0.0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    double selHandicap2 = 0.0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_to_BACKOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
      selHandicap2 = 0.0;
    } else if (*it == TwoCombination::BACKCS_0_0_to_BACKOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
      selHandicap2 = 0.0;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_BACKTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
      selHandicap2 = -1.0;
    } else if (*it == TwoCombination::BACKOU15_UNDER_to_BACKTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221385;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
      selHandicap2 = -2.0;
    } else if (*it == TwoCombination::BACKOU25_UNDER_to_BACKTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47972;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
      selHandicap2 = -3.0;
    } else if (*it == TwoCombination::BACKOU35_UNDER_to_BACKTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222344;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
      selHandicap2 = -4.0;
    } else if (*it == TwoCombination::BACKOU45_UNDER_to_BACKTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222347;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
      selHandicap2 = -5.0;
    }
    AccountsHandler ah(0, 120.0);
    initAccountsHandler(ah, 250.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_handicap = selHandicap1;
    sel1.m_availableToBackPrice.push_back(4);
    sel1.m_availableToBackSize.push_back(37.73);
    sel1.m_availableToLayPrice.push_back(2.02);
    sel1.m_availableToLaySize.push_back(849.19);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_handicap = selHandicap2;
    sel2.m_availableToBackPrice.push_back(3.5);
    sel2.m_availableToBackSize.push_back(500);
    sel2.m_availableToLayPrice.push_back(2.6);
    sel2.m_availableToLaySize.push_back(297);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;


    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == selHandicap1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 4.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_size == 37.73, "size");

    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == selHandicap2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 3.5, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(std::fabs(placeBets[market2.m_marketId].front().m_limitOrder.m_size - 43.1) < 0.1, "size");
  }
}

void BetLibUnitTestsTest::found_ImpliedMaxExposure2_Take_back_back() {
  QVERIFY(m_twoCombBackBackList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackBackList.begin();
       it != m_twoCombBackBackList.end(); it++) {
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_to_BACKOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_BACKOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_BACKTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_UNDER_to_BACKTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221385;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_UNDER_to_BACKTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47972;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_UNDER_to_BACKTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222344;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_UNDER_to_BACKTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222347;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }
    AccountsHandler ah(0, 120.0);
    initAccountsHandler(ah, 250.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(4);
    sel1.m_availableToBackSize.push_back(37.73);
    sel1.m_availableToLayPrice.push_back(2.02);
    sel1.m_availableToLaySize.push_back(849.19);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(3.5);
    sel2.m_availableToBackSize.push_back(38.26);
    sel2.m_availableToLayPrice.push_back(2.6);
    sel2.m_availableToLaySize.push_back(297);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;


    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 4.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_size == 33.4, "size");

    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 3.5, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_size == 38.26, "size");
  }
}

void BetLibUnitTestsTest::take_and_NoTake_back_back() {

}

void BetLibUnitTestsTest::take_and_take_back_back() {
  /*
  BetHandler betHandler(0, 125.0);

  QString eventId = "27517556";

  BetfairMarket market1a("1.120193205", "Correct Score", 0.0);
  market1a.m_marketStatus = BfMarketStatus::OPEN;
  BetfairSelection sel1a(1, "0 - 0");
  sel1a.m_availableToBackPrice.push_back(1.99);
  sel1a.m_availableToBackSize.push_back(1643.0);
  sel1a.m_availableToLayPrice.push_back(2.02);
  sel1a.m_availableToLaySize.push_back(849.19);
  market1a.m_selections.push_back(sel1a);

  BetfairMarket market2a("1.120148300", "Over/Under 0.5 Goals", 0.0);
  market2a.m_marketStatus = BfMarketStatus::OPEN;
  BetfairSelection sel2a(5851483, "Over 0.5 Goals");
  sel2a.m_availableToBackPrice.push_back(5);
  sel2a.m_availableToBackSize.push_back(24226);
  sel2a.m_availableToLayPrice.push_back(2.6);
  sel2a.m_availableToLaySize.push_back(297);
  market2a.m_selections.push_back(sel2a);

  BetfairMarket market1b("1.120193194", "Over/Under 4.5 Goals", 0.0);
  market1b.m_marketStatus = BfMarketStatus::OPEN;
  BetfairSelection sel1b(1222347, "Under 4.5 Goals");
  sel1b.m_availableToBackPrice.push_back(1.99);
  sel1b.m_availableToBackSize.push_back(1643.0);
  sel1b.m_availableToLayPrice.push_back(2.02);
  sel1b.m_availableToLaySize.push_back(849.19);
  market1b.m_selections.push_back(sel1b);

  BetfairMarket market2b("1.120193195", "Total Goals", 0.0);
  market2b.m_marketStatus = BfMarketStatus::OPEN;
  BetfairSelection sel2b(285473, "5 goals or more");
  sel2b.m_availableToBackPrice.push_back(5);
  sel2b.m_availableToBackSize.push_back(24226);
  sel2b.m_availableToLayPrice.push_back(2.6);
  sel2b.m_availableToLaySize.push_back(297);
  market2b.m_selections.push_back(sel2b);

  std::list<BetfairMarket> markets;
  markets.push_back(market1a);
  markets.push_back(market2a);
  markets.push_back(market1b);
  markets.push_back(market2b);

  std::map<QString, std::list<BfPlaceInstruction> > placeBets;

  betHandler.chooseBets(eventId, markets, placeBets);

  QVERIFY2(placeBets.size() == 4, QString("found=%1 expected=2")
           .arg(QString::number(placeBets.size())).toStdString().c_str());

  QVERIFY2(placeBets[market1a.m_marketId].size() == 1, "");
  QVERIFY2(placeBets[market1a.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
  QVERIFY2(placeBets[market1a.m_marketId].front().m_selectionId == 1, "");
  QVERIFY2(placeBets[market1a.m_marketId].front().m_handicap == 0.0, "");
  QVERIFY2(placeBets[market1a.m_marketId].front().m_side == BfSide::BACK, "");
  QVERIFY2(placeBets[market1a.m_marketId].front().m_limitOrder.m_price == 1.99, "");
  QVERIFY2(placeBets[market1a.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

  QVERIFY2(std::fabs(placeBets[market1a.m_marketId].front().m_limitOrder.m_size-89.4134) < 0.1, "size");

  QVERIFY2(placeBets[market2a.m_marketId].size() == 1, "");
  QVERIFY2(placeBets[market2a.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
  QVERIFY2(placeBets[market2a.m_marketId].front().m_selectionId == 5851483, "");
  QVERIFY2(placeBets[market2a.m_marketId].front().m_handicap == 0.0, "");
  QVERIFY2(placeBets[market2a.m_marketId].front().m_side == BfSide::BACK, "");
  QVERIFY2(placeBets[market2a.m_marketId].front().m_limitOrder.m_price == 5.0, "");
  QVERIFY2(placeBets[market2a.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

  QVERIFY2(placeBets[market1b.m_marketId].size() == 1, "");
  QVERIFY2(placeBets[market1b.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
  QVERIFY2(placeBets[market1b.m_marketId].front().m_selectionId == 1222347, "");
  QVERIFY2(placeBets[market1b.m_marketId].front().m_handicap == 0.0, "");
  QVERIFY2(placeBets[market1b.m_marketId].front().m_side == BfSide::BACK, "");
  QVERIFY2(placeBets[market1b.m_marketId].front().m_limitOrder.m_price == 1.99, "");
  QVERIFY2(placeBets[market1b.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

  QVERIFY2(std::fabs(placeBets[market1b.m_marketId].front().m_limitOrder.m_size-89.4134) < 0.1, "size");

  QVERIFY2(placeBets[market2b.m_marketId].size() == 1, "");
  QVERIFY2(placeBets[market2b.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
  QVERIFY2(placeBets[market2b.m_marketId].front().m_selectionId == 285473, "");
  QVERIFY2(placeBets[market2b.m_marketId].front().m_handicap == 0.0, "");
  QVERIFY2(placeBets[market2b.m_marketId].front().m_side == BfSide::BACK, "");
  QVERIFY2(placeBets[market2b.m_marketId].front().m_limitOrder.m_price == 5.0, "");
  QVERIFY2(placeBets[market2b.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

  QVERIFY2(std::fabs(placeBets[market2b.m_marketId].front().m_limitOrder.m_size-35.5866) < 0.1, "size");
  */
}

void BetLibUnitTestsTest::noFound_NoTake_back_to_lay() {
  QVERIFY(m_twoCombBackLayList.size() == 16);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackLayList.begin();
       it != m_twoCombBackLayList.end(); it++) {
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Over 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Over 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Over 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Over 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Over 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }    else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Next Goal";
      marketId2 = "1.120134273";
      selName2="No Goal";
      selId2 = 69852;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Correct Score";
      marketId2 = "1.120193205";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="1 goals or more";
      selId1 = 285469;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="2 goals or more";
      selId1 = 285470;
      marketName2 = "Over/Under 1.5 Goals";
      marketId2 = "1.120193192";
      selName2="Over 1.5 Goals";
      selId2 = 1221386;
    } else if (*it == TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="3 goals or more";
      selId1 = 285471;
      marketName2 = "Over/Under 2.5 Goals";
      marketId2 = "1.120193206";
      selName2="Over 2.5 Goals";
      selId2 = 47973;
    } else if (*it == TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="4 goals or more";
      selId1 = 2795170;
      marketName2 = "Over/Under 3.5 Goals";
      marketId2 = "1.120193193";
      selName2="Over 3.5 Goals";
      selId2 = 1222345;
    } else if (*it == TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="5 goals or more";
      selId1 = 285473;
      marketName2 = "Over/Under 4.5 Goals";
      marketId2 = "1.120193194";
      selName2="Over 4.5 Goals";
      selId2 = 1222346;
    } else if (*it == TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0) {
      marketName1 = "Next Goal";
      marketId1 = "1.120538115";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Correct Score";
      marketId2 = "1.120538119";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL) {
      marketName1 = "Correct Score";
      marketId1 = "1.120538119";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Next Goal";
      marketId2 = "1.120538115";
      selName2="No Goal";
      selId2 = 69852;
    }

    AccountsHandler ah(0, 125.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 350.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(2.02);
    sel1.m_availableToBackSize.push_back(1009.18);
    sel1.m_availableToLayPrice.push_back(17);
    sel1.m_availableToLaySize.push_back(47.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.99);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(2.02);
    sel2.m_availableToLaySize.push_back(849.19);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;


    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 0, QString("found=%1 expected=0")
             .arg(QString::number(placeBets.size())).toStdString().c_str());
  }
}

void BetLibUnitTestsTest::found_underMaxExposure_Take_back_to_lay() {
  QVERIFY(m_twoCombBackLayList.size() == 16);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackLayList.begin();
       it != m_twoCombBackLayList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Over 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Over 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Over 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Over 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Over 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Next Goal";
      marketId2 = "1.120134273";
      selName2="No Goal";
      selId2 = 69852;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Correct Score";
      marketId2 = "1.120193205";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="1 goals or more";
      selId1 = 285469;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="2 goals or more";
      selId1 = 285470;
      marketName2 = "Over/Under 1.5 Goals";
      marketId2 = "1.120193192";
      selName2="Over 1.5 Goals";
      selId2 = 1221386;
    } else if (*it == TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="3 goals or more";
      selId1 = 285471;
      marketName2 = "Over/Under 2.5 Goals";
      marketId2 = "1.120193206";
      selName2="Over 2.5 Goals";
      selId2 = 47973;
    } else if (*it == TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="4 goals or more";
      selId1 = 2795170;
      marketName2 = "Over/Under 3.5 Goals";
      marketId2 = "1.120193193";
      selName2="Over 3.5 Goals";
      selId2 = 1222345;
    } else if (*it == TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="5 goals or more";
      selId1 = 285473;
      marketName2 = "Over/Under 4.5 Goals";
      marketId2 = "1.120193194";
      selName2="Over 4.5 Goals";
      selId2 = 1222346;
    } else if (*it == TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0) {
      marketName1 = "Next Goal";
      marketId1 = "1.120538115";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Correct Score";
      marketId2 = "1.120538119";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL) {
      marketName1 = "Correct Score";
      marketId1 = "1.120538119";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Next Goal";
      marketId2 = "1.120538115";
      selName2="No Goal";
      selId2 = 69852;
    }
    AccountsHandler ah(0, 500.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 20000.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(16);
    sel1.m_availableToBackSize.push_back(2000);
    sel1.m_availableToLayPrice.push_back(17);
    sel1.m_availableToLaySize.push_back(47.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.99);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(5);
    sel2.m_availableToLaySize.push_back(2000.0);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 16, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    //QVERIFY2(std::fabs(placeBets[market1.m_marketId].front().m_limitOrder.m_size-89.4134) < 0.1, "size");



    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 5.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    //QVERIFY2(std::fabs(placeBets[market2.m_marketId].front().m_limitOrder.m_size-35.5866) < 0.1, "size");
  }
}

void BetLibUnitTestsTest::found_ImpliedMaxExposure1_Take_back_to_lay() {
  QVERIFY(m_twoCombBackLayList.size() == 16);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackLayList.begin();
       it != m_twoCombBackLayList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Over 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Over 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Over 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Over 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Over 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Next Goal";
      marketId2 = "1.120134273";
      selName2="No Goal";
      selId2 = 69852;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Correct Score";
      marketId2 = "1.120193205";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="1 goals or more";
      selId1 = 285469;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="2 goals or more";
      selId1 = 285470;
      marketName2 = "Over/Under 1.5 Goals";
      marketId2 = "1.120193192";
      selName2="Over 1.5 Goals";
      selId2 = 1221386;
    } else if (*it == TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="3 goals or more";
      selId1 = 285471;
      marketName2 = "Over/Under 2.5 Goals";
      marketId2 = "1.120193206";
      selName2="Over 2.5 Goals";
      selId2 = 47973;
    } else if (*it == TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="4 goals or more";
      selId1 = 2795170;
      marketName2 = "Over/Under 3.5 Goals";
      marketId2 = "1.120193193";
      selName2="Over 3.5 Goals";
      selId2 = 1222345;
    } else if (*it == TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="5 goals or more";
      selId1 = 285473;
      marketName2 = "Over/Under 4.5 Goals";
      marketId2 = "1.120193194";
      selName2="Over 4.5 Goals";
      selId2 = 1222346;
    } else if (*it == TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0) {
      marketName1 = "Next Goal";
      marketId1 = "1.120538115";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Correct Score";
      marketId2 = "1.120538119";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL) {
      marketName1 = "Correct Score";
      marketId1 = "1.120538119";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Next Goal";
      marketId2 = "1.120538115";
      selName2="No Goal";
      selId2 = 69852;
    }
    AccountsHandler ah(0, 500.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 40000.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(44);
    sel1.m_availableToBackSize.push_back(32.45);
    sel1.m_availableToLayPrice.push_back(17);
    sel1.m_availableToLaySize.push_back(47.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.99);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(1.1);
    sel2.m_availableToLaySize.push_back(1415.25);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 44, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_size == 32.45, "size");



    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 1.1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(std::fabs(placeBets[market2.m_marketId].front().m_limitOrder.m_size-1298) < 0.1, "size");
  }
}

void BetLibUnitTestsTest::found_TakeSize1ToSmall_Take_back_to_lay() {
  QVERIFY(m_twoCombBackLayList.size() == 16);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackLayList.begin();
       it != m_twoCombBackLayList.end(); it++) {
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Over 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Over 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Over 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Over 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Over 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Next Goal";
      marketId2 = "1.120134273";
      selName2="No Goal";
      selId2 = 69852;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Correct Score";
      marketId2 = "1.120193205";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="1 goals or more";
      selId1 = 285469;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="2 goals or more";
      selId1 = 285470;
      marketName2 = "Over/Under 1.5 Goals";
      marketId2 = "1.120193192";
      selName2="Over 1.5 Goals";
      selId2 = 1221386;
    } else if (*it == TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="3 goals or more";
      selId1 = 285471;
      marketName2 = "Over/Under 2.5 Goals";
      marketId2 = "1.120193206";
      selName2="Over 2.5 Goals";
      selId2 = 47973;
    } else if (*it == TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="4 goals or more";
      selId1 = 2795170;
      marketName2 = "Over/Under 3.5 Goals";
      marketId2 = "1.120193193";
      selName2="Over 3.5 Goals";
      selId2 = 1222345;
    } else if (*it == TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="5 goals or more";
      selId1 = 285473;
      marketName2 = "Over/Under 4.5 Goals";
      marketId2 = "1.120193194";
      selName2="Over 4.5 Goals";
      selId2 = 1222346;
    } else if (*it == TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0) {
      marketName1 = "Next Goal";
      marketId1 = "1.120538115";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Correct Score";
      marketId2 = "1.120538119";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL) {
      marketName1 = "Correct Score";
      marketId1 = "1.120538119";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Next Goal";
      marketId2 = "1.120538115";
      selName2="No Goal";
      selId2 = 69852;
    }
    AccountsHandler ah(0, 120.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 500.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(7.2);
    sel1.m_availableToBackSize.push_back(128.02);
    sel1.m_availableToLayPrice.push_back(17);
    sel1.m_availableToLaySize.push_back(47.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.99);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(1.95);
    sel2.m_availableToLaySize.push_back(192.64);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 7.2, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_size == 30.0, "size");



    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 1.95, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(std::fabs(placeBets[market2.m_marketId].front().m_limitOrder.m_size-94.7) < 0.1, "size");
  }
}

void BetLibUnitTestsTest::found_TakeSize2ToSmall_Take_back_to_lay() {

}

void BetLibUnitTestsTest::found_TakeSize1AndSize2ToSmall_NoTake_back_to_lay() {
  QVERIFY(m_twoCombBackLayList.size() == 16);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackLayList.begin();
       it != m_twoCombBackLayList.end(); it++) {
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Over 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Over 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Over 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Over 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Over 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Next Goal";
      marketId2 = "1.120134273";
      selName2="No Goal";
      selId2 = 69852;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Correct Score";
      marketId2 = "1.120193205";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="1 goals or more";
      selId1 = 285469;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="2 goals or more";
      selId1 = 285470;
      marketName2 = "Over/Under 1.5 Goals";
      marketId2 = "1.120193192";
      selName2="Over 1.5 Goals";
      selId2 = 1221386;
    } else if (*it == TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="3 goals or more";
      selId1 = 285471;
      marketName2 = "Over/Under 2.5 Goals";
      marketId2 = "1.120193206";
      selName2="Over 2.5 Goals";
      selId2 = 47973;
    } else if (*it == TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="4 goals or more";
      selId1 = 2795170;
      marketName2 = "Over/Under 3.5 Goals";
      marketId2 = "1.120193193";
      selName2="Over 3.5 Goals";
      selId2 = 1222345;
    } else if (*it == TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="5 goals or more";
      selId1 = 285473;
      marketName2 = "Over/Under 4.5 Goals";
      marketId2 = "1.120193194";
      selName2="Over 4.5 Goals";
      selId2 = 1222346;
    } else if (*it == TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0) {
      marketName1 = "Next Goal";
      marketId1 = "1.120538115";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Correct Score";
      marketId2 = "1.120538119";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL) {
      marketName1 = "Correct Score";
      marketId1 = "1.120538119";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Next Goal";
      marketId2 = "1.120538115";
      selName2="No Goal";
      selId2 = 69852;
    }
    AccountsHandler ah(0, 120.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 500.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(200);
    sel1.m_availableToBackSize.push_back(90.14);
    sel1.m_availableToLayPrice.push_back(17);
    sel1.m_availableToLaySize.push_back(47.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.99);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(17);
    sel2.m_availableToLaySize.push_back(84.9);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 0, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());
  }
}

void BetLibUnitTestsTest::found_ImpliedMaxExposure2_Take_back_to_lay() {
  QVERIFY(m_twoCombBackLayList.size() == 16);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombBackLayList.begin();
       it != m_twoCombBackLayList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Under 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Over 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Over 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Over 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Over 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Over 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Next Goal";
      marketId2 = "1.120134273";
      selName2="No Goal";
      selId2 = 69852;
    } else if (*it == TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851482;
      marketName2 = "Correct Score";
      marketId2 = "1.120193205";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="1 goals or more";
      selId1 = 285469;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="2 goals or more";
      selId1 = 285470;
      marketName2 = "Over/Under 1.5 Goals";
      marketId2 = "1.120193192";
      selName2="Over 1.5 Goals";
      selId2 = 1221386;
    } else if (*it == TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="3 goals or more";
      selId1 = 285471;
      marketName2 = "Over/Under 2.5 Goals";
      marketId2 = "1.120193206";
      selName2="Over 2.5 Goals";
      selId2 = 47973;
    } else if (*it == TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="4 goals or more";
      selId1 = 2795170;
      marketName2 = "Over/Under 3.5 Goals";
      marketId2 = "1.120193193";
      selName2="Over 3.5 Goals";
      selId2 = 1222345;
    } else if (*it == TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER) {
      marketName1 = "Total Goals";
      marketId1 = "1.120193195";
      selName1="5 goals or more";
      selId1 = 285473;
      marketName2 = "Over/Under 4.5 Goals";
      marketId2 = "1.120193194";
      selName2="Over 4.5 Goals";
      selId2 = 1222346;
    } else if (*it == TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0) {
      marketName1 = "Next Goal";
      marketId1 = "1.120538115";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Correct Score";
      marketId2 = "1.120538119";
      selName2="0 - 0";
      selId2 = 1;
    } else if (*it == TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL) {
      marketName1 = "Correct Score";
      marketId1 = "1.120538119";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Next Goal";
      marketId2 = "1.120538115";
      selName2="No Goal";
      selId2 = 69852;
    }
    AccountsHandler ah(0, 500.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 40000.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(44);
    sel1.m_availableToBackSize.push_back(600.45);
    sel1.m_availableToLayPrice.push_back(17);
    sel1.m_availableToLaySize.push_back(47.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.99);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(1.1);
    sel2.m_availableToLaySize.push_back(1415.25);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::BACK, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 44, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(std::fabs(placeBets[market1.m_marketId].front().m_limitOrder.m_size-35.3) < 0.1, "size");



    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 1.1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_size == 1415.25, "size");
  }
}

void BetLibUnitTestsTest::noFound_NoTake_lay_to_lay() {
  QVERIFY(m_twoCombLayLayList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombLayLayList.begin();
       it != m_twoCombLayLayList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::LAYNG_NO_GOAL_to_LAYOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::LAYCS_0_0_to_LAYOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::LAYO05_UNDER_to_LAY_TG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::LAYO15_UNDER_to_LAY_TG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::LAYO25_UNDER_to_LAY_TG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::LAYO35_UNDER_to_LAY_TG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::LAYO45_UNDER_to_LAY_TG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }
    AccountsHandler ah(0, 500.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 350.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(1.2);
    sel1.m_availableToBackSize.push_back(2000);
    sel1.m_availableToLayPrice.push_back(46);
    sel1.m_availableToLaySize.push_back(12000.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.2);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(1.05);
    sel2.m_availableToLaySize.push_back(555.0);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 0, QString("found=%1 expected=0")
             .arg(QString::number(placeBets.size())).toStdString().c_str());
  }
}

void BetLibUnitTestsTest::found_maxExposureToSmall_NoTake_lay_to_lay() {
  QVERIFY(m_twoCombLayLayList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombLayLayList.begin();
       it != m_twoCombLayLayList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::LAYNG_NO_GOAL_to_LAYOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::LAYCS_0_0_to_LAYOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::LAYO05_UNDER_to_LAY_TG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::LAYO15_UNDER_to_LAY_TG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::LAYO25_UNDER_to_LAY_TG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::LAYO35_UNDER_to_LAY_TG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::LAYO45_UNDER_to_LAY_TG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }
    AccountsHandler ah(0, 30.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 30.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(1.2);
    sel1.m_availableToBackSize.push_back(2000);
    sel1.m_availableToLayPrice.push_back(4.6);
    sel1.m_availableToLaySize.push_back(12000.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.2);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(1.13);
    sel2.m_availableToLaySize.push_back(200.0);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 0, QString("found=%1 expected=0")
             .arg(QString::number(placeBets.size())).toStdString().c_str());
  }
}

void BetLibUnitTestsTest::found_underMaxExposure_Take_lay_to_lay() {
  QVERIFY(m_twoCombLayLayList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombLayLayList.begin();
       it != m_twoCombLayLayList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::LAYNG_NO_GOAL_to_LAYOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::LAYCS_0_0_to_LAYOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::LAYO05_UNDER_to_LAY_TG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::LAYO15_UNDER_to_LAY_TG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::LAYO25_UNDER_to_LAY_TG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::LAYO35_UNDER_to_LAY_TG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::LAYO45_UNDER_to_LAY_TG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }
    AccountsHandler ah(0, 500.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 5000.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(1.2);
    sel1.m_availableToBackSize.push_back(2000);
    sel1.m_availableToLayPrice.push_back(4.6);
    sel1.m_availableToLaySize.push_back(12000.6);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.2);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(1.13);
    sel2.m_availableToLaySize.push_back(555.0);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 4.6, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    //QVERIFY2(std::fabs(placeBets[market1.m_marketId].front().m_limitOrder.m_size-89.4134) < 0.1, "size");



    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 1.13, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    //QVERIFY2(std::fabs(placeBets[market2.m_marketId].front().m_limitOrder.m_size-35.5866) < 0.1, "size");
  }
}

void BetLibUnitTestsTest::found_ImpliedMaxExposure1_Take_lay_to_lay() {
  QVERIFY(m_twoCombLayLayList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombLayLayList.begin();
       it != m_twoCombLayLayList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::LAYNG_NO_GOAL_to_LAYOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::LAYCS_0_0_to_LAYOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::LAYO05_UNDER_to_LAY_TG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::LAYO15_UNDER_to_LAY_TG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::LAYO25_UNDER_to_LAY_TG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::LAYO35_UNDER_to_LAY_TG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::LAYO45_UNDER_to_LAY_TG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }
    AccountsHandler ah(0, 500.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 5000.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(1.2);
    sel1.m_availableToBackSize.push_back(2000);
    sel1.m_availableToLayPrice.push_back(1.25);
    sel1.m_availableToLaySize.push_back(200.51);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.2);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(3.15);
    sel2.m_availableToLaySize.push_back(281.23);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 1.25, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_size == 200.51, "size");



    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 3.15, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    //QVERIFY2(std::fabs(placeBets[market2.m_marketId].front().m_limitOrder.m_size-35.5866) < 0.1, "size");
  }
}

void BetLibUnitTestsTest::found_ImpliedMaxExposure2_Take_lay_to_lay() {
  QVERIFY(m_twoCombLayLayList.size() == 7);

  for (std::list<TwoCombination::Type>::iterator it = m_twoCombLayLayList.begin();
       it != m_twoCombLayLayList.end(); it++) {
    //BetStatistics::resetPlacedBets();
    QString marketName1 = "";
    QString marketId1 = "";
    QString selName1="";
    qint64 selId1 = 0;
    QString marketName2 = "";
    QString marketId2 = "";
    QString selName2="";
    qint64 selId2 = 0;
    if (*it == TwoCombination::LAYNG_NO_GOAL_to_LAYOU05_OVER) {
      marketName1 = "Next Goal";
      marketId1 = "1.120134273";
      selName1="No Goal";
      selId1 = 69852;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851483;
    } else if (*it == TwoCombination::LAYCS_0_0_to_LAYOU05_OVER) {
      marketName1 = "Correct Score";
      marketId1 = "1.120193205";
      selName1="0 - 0";
      selId1 = 1;
      marketName2 = "Over/Under 0.5 Goals";
      marketId2 = "1.120148300";
      selName2="Over 0.5 Goals";
      selId2 = 5851482;
    } else if (*it == TwoCombination::LAYO05_UNDER_to_LAY_TG_1_OR_MORE) {
      marketName1 = "Over/Under 0.5 Goals";
      marketId1 = "1.120148300";
      selName1="Under 0.5 Goals";
      selId1 = 5851483;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="1 goals or more";
      selId2 = 285469;
    } else if (*it == TwoCombination::LAYO15_UNDER_to_LAY_TG_2_OR_MORE) {
      marketName1 = "Over/Under 1.5 Goals";
      marketId1 = "1.120193192";
      selName1="Under 1.5 Goals";
      selId1 = 1221386;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="2 goals or more";
      selId2 = 285470;
    } else if (*it == TwoCombination::LAYO25_UNDER_to_LAY_TG_3_OR_MORE) {
      marketName1 = "Over/Under 2.5 Goals";
      marketId1 = "1.120193206";
      selName1="Under 2.5 Goals";
      selId1 = 47973;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="3 goals or more";
      selId2 = 285471;
    } else if (*it == TwoCombination::LAYO35_UNDER_to_LAY_TG_4_OR_MORE) {
      marketName1 = "Over/Under 3.5 Goals";
      marketId1 = "1.120193193";
      selName1="Under 3.5 Goals";
      selId1 = 1222345;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="4 goals or more";
      selId2 = 2795170;
    } else if (*it == TwoCombination::LAYO45_UNDER_to_LAY_TG_5_OR_MORE) {
      marketName1 = "Over/Under 4.5 Goals";
      marketId1 = "1.120193194";
      selName1="Under 4.5 Goals";
      selId1 = 1222346;
      marketName2 = "Total Goals";
      marketId2 = "1.120193195";
      selName2="5 goals or more";
      selId2 = 285473;
    }
    AccountsHandler ah(0, 500.0);
    EventStats es;
    setZeroTotalGoals("27517556", es);
    initAccountsHandler(ah, 5000.0);
    BetHandler betHandler(0, &ah, &es, &m_configUT);

    BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                  QDateTime::currentDateTimeUtc().toString());

    BetfairMarket market1(marketId1, marketName1, 0.0);
    market1.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel1(selId1, selName1);
    sel1.m_availableToBackPrice.push_back(1.2);
    sel1.m_availableToBackSize.push_back(2000);
    sel1.m_availableToLayPrice.push_back(1.25);
    sel1.m_availableToLaySize.push_back(776.81);
    market1.m_selections.push_back(sel1);

    BetfairMarket market2(marketId2, marketName2, 0.0);
    market2.m_marketStatus = BfMarketStatus::OPEN;
    BetfairSelection sel2(selId2, selName2);
    sel2.m_availableToBackPrice.push_back(1.2);
    sel2.m_availableToBackSize.push_back(1643.0);
    sel2.m_availableToLayPrice.push_back(3.15);
    sel2.m_availableToLaySize.push_back(50.23);
    market2.m_selections.push_back(sel2);

    std::list<BetfairMarket> markets;
    markets.push_back(market1);
    markets.push_back(market2);

    std::map<QString, std::list<BfPlaceInstruction> > placeBets;

    betHandler.chooseBets(event, markets, placeBets);

    QVERIFY2(placeBets.size() == 2, QString("found=%1 expected=2")
             .arg(QString::number(placeBets.size())).toStdString().c_str());

    QVERIFY2(placeBets[market1.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_selectionId == selId1, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_price == 1.25, "");
    QVERIFY2(placeBets[market1.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(std::fabs(placeBets[market1.m_marketId].front().m_limitOrder.m_size-126.6) < 0.1, "size");



    QVERIFY2(placeBets[market2.m_marketId].size() == 1, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_orderType == BfOrderType::LIMIT, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_selectionId == selId2, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_handicap == 0.0, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_side == BfSide::LAY, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_price == 3.15, "");
    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "");

    QVERIFY2(placeBets[market2.m_marketId].front().m_limitOrder.m_size == 50.23, "size");
  }
}

void BetLibUnitTestsTest::tc_BetStatistics_hasActiveCombinations_2CombBothSuccssfull() {
  BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                QDateTime::currentDateTimeUtc().toString());
  BetfairMarket bfmarket1("1.120193194", "Over/Under 4.5 Goals", 0.0);
  QString selName1="Under 4.5 Goals";
  qint64 selId1 = 1222346;
  double selHandicap1 = 0.0;
  BetfairMarket bfmarket2("1.120193195", "Total Goals", 0.0);
  QString selName2="5 goals or more";
  qint64 selId2 = 285473;
  double selHandicap2 = 0.0;

  BfPlaceInstruction pi1(BfOrderType::LIMIT, selId1, selHandicap1, BfSide::BACK,
                         BfLimitOrder(4.6, 120.0, BfPersistenceType::LAPSE));
  BfPlaceInstruction pi2(BfOrderType::LIMIT, selId2, selHandicap2, BfSide::BACK,
                         BfLimitOrder(4.6, 120.0, BfPersistenceType::LAPSE));
  BetStatistics bs(false);

  // Test no bets placed
  QVERIFY(bs.hasActiveCombinations(event.m_eventId) == false);

  // Placing bets on 1 event
  bs.placeBets(event, bfmarket1, bfmarket2, pi1, pi2);
  QVERIFY(bs.hasActiveCombinations(event.m_eventId) == true);

  // Receiving placeOrderResponse for first market
  BfPlaceExecutionReport placeReport1;
  placeReport1.m_status = BfExecutionReportStatus::SUCCESS;
  placeReport1.m_marketId = bfmarket1.m_marketId;

  BfPlaceInstructionReport bfpireport1;
  bfpireport1.m_status = BfInstructionReportStatus::SUCCESS;
  bfpireport1.m_betId = "11111";
  bfpireport1.m_placeDate = QDateTime::currentDateTimeUtc();
  bfpireport1.m_placeInstruction = pi1;

  placeReport1.m_instructionReports.push_back(bfpireport1);

  bs.placeOrdersRsp(placeReport1);
  QVERIFY(bs.hasActiveCombinations(event.m_eventId) == true);

  // Receiving placeOrderResponse for first market
  BfPlaceExecutionReport placeReport2;
  placeReport2.m_status = BfExecutionReportStatus::SUCCESS;
  placeReport2.m_marketId = bfmarket2.m_marketId;

  BfPlaceInstructionReport bfpireport2;
  bfpireport2.m_status = BfInstructionReportStatus::SUCCESS;
  bfpireport2.m_betId = "11111";
  bfpireport2.m_placeDate = QDateTime::currentDateTimeUtc();
  bfpireport2.m_placeInstruction = pi2;

  placeReport2.m_instructionReports.push_back(bfpireport2);

  bs.placeOrdersRsp(placeReport2);
  QVERIFY(bs.hasActiveCombinations(event.m_eventId) == false);
}

void BetLibUnitTestsTest::tc_BetStatistics_hasActiveCombinations_2CombPartlySuccssfull() {
  BfEvent event("27517556", "dummyEventName", "dummyLocale", "dummyTimeZone",
                QDateTime::currentDateTimeUtc().toString());
  BetfairMarket bfmarket1("1.120193194", "Over/Under 4.5 Goals", 0.0);
  QString selName1="Under 4.5 Goals";
  qint64 selId1 = 1222346;
  double selHandicap1 = 0.0;
  BetfairMarket bfmarket2("1.120193195", "Total Goals", 0.0);
  QString selName2="5 goals or more";
  qint64 selId2 = 285473;
  double selHandicap2 = 0.0;

  BfPlaceInstruction pi1(BfOrderType::LIMIT, selId1, selHandicap1, BfSide::BACK,
                         BfLimitOrder(4.6, 120.0, BfPersistenceType::LAPSE));
  BfPlaceInstruction pi2(BfOrderType::LIMIT, selId2, selHandicap2, BfSide::BACK,
                         BfLimitOrder(4.6, 120.0, BfPersistenceType::LAPSE));
  BetStatistics bs(false);

  // Test no bets placed
  QVERIFY(bs.hasActiveCombinations(event.m_eventId) == false);

  // Placing bets on 1 event
  bs.placeBets(event, bfmarket1, bfmarket2, pi1, pi2);
  QVERIFY(bs.hasActiveCombinations(event.m_eventId) == true);

  // Receiving placeOrderResponse for first market
  BfPlaceExecutionReport placeReport1;
  placeReport1.m_status = BfExecutionReportStatus::SUCCESS;
  placeReport1.m_marketId = bfmarket1.m_marketId;

  BfPlaceInstructionReport bfpireport1;
  bfpireport1.m_status = BfInstructionReportStatus::SUCCESS;
  bfpireport1.m_betId = "11111";
  bfpireport1.m_placeDate = QDateTime::currentDateTimeUtc();
  bfpireport1.m_placeInstruction = pi1;

  placeReport1.m_instructionReports.push_back(bfpireport1);

  bs.placeOrdersRsp(placeReport1);
  QVERIFY(bs.hasActiveCombinations(event.m_eventId) == true);

  // Receiving placeOrderResponse for first market
  BfPlaceExecutionReport placeReport2;
  placeReport2.m_status = BfExecutionReportStatus::FAILURE;
  placeReport2.m_marketId = bfmarket2.m_marketId;

  BfPlaceInstructionReport bfpireport2;
  bfpireport2.m_status = BfInstructionReportStatus::FAILURE;
  bfpireport2.m_betId = "11111";
  bfpireport2.m_placeDate = QDateTime::currentDateTimeUtc();
  bfpireport2.m_placeInstruction = pi2;

  placeReport2.m_instructionReports.push_back(bfpireport2);

  bs.placeOrdersRsp(placeReport2);
  QVERIFY(bs.hasActiveCombinations(event.m_eventId) == true);
}

void BetLibUnitTestsTest::tc_EventDataConsumer_loggingevent_finnish() {
  // Writing to file a couple of times

  // sending finish
}

void BetLibUnitTestsTest::tc_EventDataConsumer_loggingevent_abortEvent() {
  // Writing to file a couple of times

  // sending abort event
}

void BetLibUnitTestsTest::tc_EventDataConsumer_nologgingevent_abortEvent() {

}

QTEST_APPLESS_MAIN(BetLibUnitTestsTest)

#include "tst_betlibunitteststest.moc"
