#ifndef BFMARKETTYPE_H
#define BFMARKETTYPE_H

#include <QString>

class BfMarketType {
public:
  enum Type {
    MATCH_ODDS,
    CORRECT_SCORE,
    CORRECT_SCORE2,
    TOTAL_GOALS,
    OVER_UNDER_05,
    OVER_UNDER_15,
    OVER_UNDER_25,
    OVER_UNDER_35,
    OVER_UNDER_45,
    OVER_UNDER_55,
    OVER_UNDER_65,
    OVER_UNDER_75,
    OVER_UNDER_85,


    GOAL_BOTH_HALVES,
    ASIAN_HANDICAP,
    WINCAST,



    OVER_UNDER_55_CORNR,
    OVER_UNDER_85_CORNR,
    OVER_UNDER_105_CORNR,
    OVER_UNDER_135_CORNR,

    OVER_UNDER_25_CARDS,
    OVER_UNDER_45_CARDS,
    OVER_UNDER_65_CARDS,

    HALF_WITH_MOST_GOALS,

    EXACT_GOALS,
    WIN_HALF,
    TEAM_B_WIN_TO_NIL,
    TO_SCORE_HATTRICK,

    WINNING_MARGIN,
    WIN_FROM_BEHIND,
    TO_SCORE_2_OR_MORE,

    TEAM_A_WIN_TO_NIL,

    TEAM_TOTAL_GOALS,
    DOUBLE_CHANCE,
    SHOWN_A_CARD,
    FIRST_HALF_GOALS_05,
    TEAM_B_2,
    MATCH_ODDS_AND_BTTS,
    FIRST_CORNER,
    FIRST_HALF_GOALS_25,
    PENALTY_TAKEN,
    RACE_TO_3_GOALS,
    RACE_TO_2_GOALS,


    FIRST_HALF_GOALS_15,
    TEAM_A_3,
    CORNER_MATCH_BET,
    FIRST_HALF_CORNERS,
    TO_SCORE_BOTH_HALVES,

    ODD_OR_EVEN,
    MATCH_ODDS_AND_OU_25,
    TEAM_B_1,
    CLEAN_SHEET,
    SENDING_OFF,
    TEAM_A_1,

    HAT_TRICKED_SCORED,
    TEAM_B_3,
    TEAM_A_2,
    HALF_TIME,
    TO_SCORE,
    HALF_TIME_FULL_TIME,
    AH_ODDS_MARKET,

    HALF_TIME_SCORE,
    BOOKING_ODDS,
    CORNER_ODDS,

    FIRST_GOAL_SCORER,
    FIRST_GOAL_ODDS,
    WIN_BOTH_HALVES,
    BOOKING_MATCH_BET,
    NEXT_GOAL,
    SCORE_CAST,
    BOTH_TEAMS_TO_SCORE,
    DRAW_NO_BET,
  };

  static QString toString(const Type t) {
    if (t == MATCH_ODDS) {
      return QString("MATCH_ODDS");
    } else if (t == CORRECT_SCORE) {
      return QString("CORRECT_SCORE");
    } else if (t == CORRECT_SCORE2) {
      return QString("CORRECT_SCORE2");
    } else if (t == TOTAL_GOALS) {
      return QString("TOTAL_GOALS");
    } else if (t == OVER_UNDER_05) {
      return QString("OVER_UNDER_05");
    } else if (t == OVER_UNDER_15) {
      return QString("OVER_UNDER_15");
    } else if (t == OVER_UNDER_25) {
      return QString("OVER_UNDER_25");
    } else if (t == OVER_UNDER_35) {
      return QString("OVER_UNDER_35");
    } else if (t == OVER_UNDER_45) {
      return QString("OVER_UNDER_45");
    } else if (t == OVER_UNDER_55) {
      return QString("OVER_UNDER_55");
    } else if (t == OVER_UNDER_65) {
      return QString("OVER_UNDER_65");
    } else if (t == OVER_UNDER_75) {
      return QString("OVER_UNDER_75");
    } else if (t == OVER_UNDER_85) {
      return QString("OVER_UNDER_85");
    } else if (t == NEXT_GOAL) {
      return QString("NEXT_GOAL");
    } else if (t == EXACT_GOALS) {
      return QString("EXACT_GOALS");
    } else if (t == HALF_TIME) {
      return QString("HALF_TIME");
    } else if (t == HALF_TIME_FULL_TIME) {
      return QString("HALF_TIME_FULL_TIME");
    } else if (t == HALF_TIME_SCORE) {
      return QString("HALF_TIME_SCORE");
    }

    else if (t == GOAL_BOTH_HALVES) {
      return QString("GOAL_BOTH_HALVES");
    } else if (t == ASIAN_HANDICAP) {
      return QString("ASIAN_HANDICAP");
    } else if (t == WINCAST) {
      return QString("WINCAST");
    } else if (t == OVER_UNDER_55_CORNR) {
      return QString("OVER_UNDER_55_CORNR");
    } else if (t == OVER_UNDER_85_CORNR) {
      return QString("OVER_UNDER_85_CORNR");
    } else if (t == OVER_UNDER_105_CORNR) {
      return QString("OVER_UNDER_105_CORNR");
    } else if (t == OVER_UNDER_135_CORNR) {
      return QString("OVER_UNDER_135_CORNR");
    } else if (t == OVER_UNDER_25_CARDS) {
      return QString("OVER_UNDER_25_CARDS");
    } else if (t == OVER_UNDER_45_CARDS) {
      return QString("OVER_UNDER_45_CARDS");
    } else if (t == OVER_UNDER_65_CARDS) {
      return QString("OVER_UNDER_65_CARDS");
    } else if (t == HALF_WITH_MOST_GOALS) {
      return QString("HALF_WITH_MOST_GOALS");
    } else if (t == EXACT_GOALS) {
      return QString("EXACT_GOALS");
    }




    throw(std::bad_exception());

    return QString("UNKNOWN");
  }
};

#endif // BFMARKETTYPE_H

