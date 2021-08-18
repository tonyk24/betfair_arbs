#ifndef BETHANDLER_H
#define BETHANDLER_H

#include <map>
#include <list>
#include <utility>

#include <QString>
#include <QObject>
#include <QDebug>

#include "betlib_global.h"

#include "bftypes/bfplaceexecutionreport.h"
#include "bftypes/bfmarket.h"
#include "bftypes/bfselection.h"
#include "bftypes/bfplaceinstruction.h"
#include "betting/betstatistics.h"
#include "betting/accountshandler.h"
#include "betting/eventstats.h"

#include "misc/config.h"

using namespace BfLib;

class TwoCombination {
public:
  /*
   * C Back_Next_Goal_No Goal, Back_OverUnder_0.5_Goals_Over 0.5 Goals
   * Back_Correct_Score_0 - 0, Back_OverUnder_0.5_Goals_Over 0.5 Goals
   * Back_OverUnder_0.5_Goals_Under 0.5 Goals, Back_Total_Goals_1 goals or more
   * Back_OverUnder_1.5_Goals_Under 1.5 Goals, Back_Total_Goals_2 goals or more
   * Back_OverUnder_2.5_Goals_Under 2.5 Goals, Back_Total_Goals_3 goals or more
   * Back_OverUnder_4.5_Goals_Under 4.5 Goals, Back_Total_Goals_5 goals or more
   * Back_OverUnder_3.5_Goals_Under 3.5 Goals, Back_Total_Goals_4 goals or more
   *
   * Back_Next_Goal_No Goal, Lay_OverUnder_0.5_Goals_Under 0.5 Goals
   * Back_Correct_Score_0 - 0, Lay_OverUnder_0.5_Goals_Under 0.5 Goals
   * Back_OverUnder_0.5_Goals_Over 0.5 Goals, Lay_Total_Goals_1 goals or more
   * Back_OverUnder_4.5_Goals_Over 4.5 Goals, Lay_Total_Goals_5 goals or more
   * Back_OverUnder_1.5_Goals_Over 1.5 Goals, Lay_Total_Goals_2 goals or more
   * Back_OverUnder_2.5_Goals_Over 2.5 Goals, Lay_Total_Goals_3 goals or more
   * Back_OverUnder_3.5_Goals_Over 3.5 Goals, Lay_Total_Goals_4 goals or more
   *
   * Back_Total_Goals_4 goals or more, Lay_OverUnder_3.5_Goals_Over 3.5 Goals
   * Back_Total_Goals_5 goals or more, Lay_OverUnder_4.5_Goals_Over 4.5 Goals
   * Back_Total_Goals_3 goals or more, Lay_OverUnder_2.5_Goals_Over 2.5 Goals
   * Back_Total_Goals_2 goals or more, Lay_OverUnder_1.5_Goals_Over 1.5 Goals
   * Back_Total_Goals_1 goals or more, Lay_OverUnder_0.5_Goals_Over 0.5 Goals
   * Back_OverUnder_0.5_Goals_Under 0.5 Goals, Lay_Next_Goal_No Goal
   * Back_OverUnder_0.5_Goals_Under 0.5 Goals, Lay_Correct_Score_0 - 0
   *
   * Back_Next_Goal_No Goal, Lay_Correct_Score_0 - 0
   * Back_Correct_Score_0 - 0, Lay_Next_Goal_No Goal
   *
   * Lay_OverUnder_2.5_Goals_Under 2.5 Goals, Lay_Total_Goals_3 goals or more
   * Lay_OverUnder_1.5_Goals_Under 1.5 Goals, Lay_Total_Goals_2 goals or more
   * Lay_Next_Goal_No Goal, Lay_OverUnder_0.5_Goals_Over 0.5 Goals
   * Lay_Correct_Score_0 - 0, Lay_OverUnder_0.5_Goals_Over 0.5 Goals
   * Lay_OverUnder_0.5_Goals_Under 0.5 Goals, Lay_Total_Goals_1 goals or more
   * Lay_OverUnder_4.5_Goals_Under 4.5 Goals, Lay_Total_Goals_5 goals or more
   * Lay_OverUnder_3.5_Goals_Under 3.5 Goals, Lay_Total_Goals_4 goals or more
   * */

  enum Type {
    // Back_Next_Goal_No Goal, Back_OverUnder_0.5_Goals_Over 0.5 Goals
    BACKNG_NO_GOAL_to_BACKOU05_OVER,
    // Back_Correct_Score_0 - 0, Back_OverUnder_0.5_Goals_Over 0.5 Goals
    BACKCS_0_0_to_BACKOU05_OVER,
    // Back_OverUnder_0.5_Goals_Under 0.5 Goals, Back_Total_Goals_1 goals or more
    BACKOU05_UNDER_to_BACKTG_1_OR_MORE,
    // Back_OverUnder_1.5_Goals_Under 1.5 Goals, Back_Total_Goals_2 goals or more
    BACKOU15_UNDER_to_BACKTG_2_OR_MORE,
    // Back_OverUnder_2.5_Goals_Under 2.5 Goals, Back_Total_Goals_3 goals or more
    BACKOU25_UNDER_to_BACKTG_3_OR_MORE,
    // Back_OverUnder_3.5_Goals_Under 3.5 Goals, Back_Total_Goals_4 goals or more
    BACKOU35_UNDER_to_BACKTG_4_OR_MORE,
    // Back_OverUnder_4.5_Goals_Under 4.5 Goals, Back_Total_Goals_5 goals or more
    BACKOU45_UNDER_to_BACKTG_5_OR_MORE,

    // Back_Next_Goal_No Goal, Lay_OverUnder_0.5_Goals_Under 0.5 Goals
    BACKNG_NO_GOAL_LAYOU05_UNDER,
    // Back_Correct_Score_0 - 0, Lay_OverUnder_0.5_Goals_Under 0.5 Goals
    BACKCS_0_0_to_LAYOU05_UNDER,
    // Back_OverUnder_0.5_Goals_Over 0.5 Goals, Lay_Total_Goals_1 goals or more
    BACKOU05_OVER_to_LAYTG_1_OR_MORE,
    // Back_OverUnder_1.5_Goals_Over 1.5 Goals, Lay_Total_Goals_2 goals or more
    BACKOU15_OVER_to_LAYTG_2_OR_MORE,
    // Back_OverUnder_2.5_Goals_Over 2.5 Goals, Lay_Total_Goals_3 goals or more
    BACKOU25_OVER_to_LAYTG_3_OR_MORE,
    // Back_OverUnder_3.5_Goals_Over 3.5 Goals, Lay_Total_Goals_4 goals or more
    BACKOU35_OVER_to_LAYTG_4_OR_MORE,
    // Back_OverUnder_4.5_Goals_Over 4.5 Goals, Lay_Total_Goals_5 goals or more
    BACKOU45_OVER_to_LAYTG_5_OR_MORE,

    // Back_OverUnder_0.5_Goals_Under 0.5 Goals, Lay_Next_Goal_No Goal
    BACKOU05_UNDER_to_LAYNG_NO_GOAL,
    // Back_OverUnder_0.5_Goals_Under 0.5 Goals, Lay_Correct_Score_0 - 0
    BACKOU05_UNDER_to_LAYCS_0_0,
    // Back_Total_Goals_1 goals or more, Lay_OverUnder_0.5_Goals_Over 0.5 Goals
    BACKTG_1_OR_MORE_to_LAYOU05_OVER,
    // Back_Total_Goals_2 goals or more, Lay_OverUnder_1.5_Goals_Over 1.5 Goals
    BACKTG_2_OR_MORE_to_LAYOU15_OVER,
    // Back_Total_Goals_3 goals or more, Lay_OverUnder_2.5_Goals_Over 2.5 Goals
    BACKTG_3_OR_MORE_to_LAYOU25_OVER,
    // Back_Total_Goals_4 goals or more, Lay_OverUnder_3.5_Goals_Over 3.5 Goals
    BACKTG_4_OR_MORE_to_LAYOU35_OVER,
    // Back_Total_Goals_5 goals or more, Lay_OverUnder_4.5_Goals_Over 4.5 Goals
    BACKTG_5_OR_MORE_to_LAYOU45_OVER,

    // Back_Next_Goal_No Goal, Lay_Correct_Score_0 - 0
    BACKNG_NO_GOAL_to_LAYCS_0_0,
    // Back_Correct_Score_0 - 0, Lay_Next_Goal_No Goal
    BACKCS_0_0_to_LAYNG_NO_GOAL,

    // Lay_Next_Goal_No Goal, Lay_OverUnder_0.5_Goals_Over 0.5 Goals
    LAYNG_NO_GOAL_to_LAYOU05_OVER,
    // Lay_Correct_Score_0 - 0, Lay_OverUnder_0.5_Goals_Over 0.5 Goals
    LAYCS_0_0_to_LAYOU05_OVER,
    // Lay_OverUnder_0.5_Goals_Under 0.5 Goals, Lay_Total_Goals_1 goals or more
    LAYO05_UNDER_to_LAY_TG_1_OR_MORE,
    // Lay_OverUnder_1.5_Goals_Under 1.5 Goals, Lay_Total_Goals_2 goals or more
    LAYO15_UNDER_to_LAY_TG_2_OR_MORE,
    // Lay_OverUnder_2.5_Goals_Under 2.5 Goals, Lay_Total_Goals_3 goals or more
    LAYO25_UNDER_to_LAY_TG_3_OR_MORE,
    // Lay_OverUnder_3.5_Goals_Under 3.5 Goals, Lay_Total_Goals_4 goals or more
    LAYO35_UNDER_to_LAY_TG_4_OR_MORE,
    // Lay_OverUnder_4.5_Goals_Under 4.5 Goals, Lay_Total_Goals_5 goals or more
    LAYO45_UNDER_to_LAY_TG_5_OR_MORE
  };
  TwoCombination(Type t) :
    market1(0),
    selection1(0),
    market2(0),
    selection2(0),
    m_type(t) {
  }

  bool hasData() {
    return market1 != 0 && selection1 != 0 &&
        market2 != 0 && selection2 != 0;
  }

  const BetfairMarket *market1;
  const BetfairSelection *selection1;
  const BetfairMarket *market2;
  const BetfairSelection *selection2;

  Type m_type;
};

class BETLIBSHARED_EXPORT BetHandler : public QObject {
  Q_OBJECT
public:

  BetHandler(QObject *parent,
             AccountsHandler *accountsHandler,
             EventStats *eventStats,
             Config *config);
  ~BetHandler();

  void chooseBets(const BfEvent &eventId,
                  const std::list<BetfairMarket> &markets,
                  std::map<QString, std::list<BfPlaceInstruction> > &placeBets);
  void doPlaceBets(const BfEvent &event,
                 const BetfairMarket &market1,
                 const BfPlaceInstruction &bet1,
                 const BetfairMarket &market2,
                 const BfPlaceInstruction &bet2,
                 std::map<QString, std::list<BfPlaceInstruction> > &placeBets);

  void placeOrdersRsp(const BfPlaceExecutionReport &placeExecutionReport);

  bool hasData(std::pair<double, double> &backFirst,
               std::pair<double, double> &backSecond) {
    if (backFirst.first >= 1.01 && // price
        backSecond.first >= 1.01 && // price
        backFirst.second > 0.0 && // size
        backSecond.second > 0.0) { // size
      return true;
    }
    return false;
  }

  void findTwoCombinations(const BfEvent &event,
                           const std::list<BetfairMarket> &markets,
                           std::list<TwoCombination> &twoCombinations);

  void findBackLayPositiveOutcome(double p1, double p2,
                                  double price1, double size1,
                                  double price2, double size2);
private:
  BetStatistics m_betStats;
  AccountsHandler *m_accountsHandler;
  EventStats *m_eventStats;
  Config *m_config;
};

#endif // BETHANDLER_H

