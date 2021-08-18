#ifndef BFFILTERFACTORY_H
#define BFFILTERFACTORY_H

#include <utility>

#include <QDateTime>

#include "betfairfilter/betfairmarketfilter.h"
#include "betfairfilter/bfmarkettype.h"
#include "bfenums/bfmarketprojection.h"

using namespace BfLib;

class BfFilterFactory {
public:
  static BetfairMarketFilter chooseEventsFilter(int eventTypeId = 1) {
    // Eventtypeid 1 = football
    // 7524 = Icehockey
    BetfairMarketFilter marketFilter;
    // Get markets that starts between 2 hours and 1 hours 45 minutes
    marketFilter.m_startAfter = new QDateTime(QDateTime::currentDateTimeUtc().addSecs(-3*60*60)); // -3 hours
    marketFilter.m_eventTypeIds.push_back(QString::number(eventTypeId));
    marketFilter.m_startBefore = new QDateTime(QDateTime::currentDateTimeUtc().addSecs(7*24*60*60)); // 1 week

    //marketFilter.m_startAfter = new QDateTime(QDateTime::currentDateTimeUtc().addSecs(-60*60));
    //marketFilter.m_startBefore = new QDateTime(QDateTime::currentDateTimeUtc().addSecs(0.25*60*60));
/*
    // Swedish
    marketFilter.m_competitionIds.push_back(BfCompetition::SWE_Allsvenskan);
    marketFilter.m_competitionIds.push_back(BfCompetition::SWE_Superettan);

    // First national legue
    marketFilter.m_competitionIds.push_back(BfCompetition::DNK_Danish_Superliga);
    marketFilter.m_competitionIds.push_back(BfCompetition::ESP_Primera_Division);
    marketFilter.m_competitionIds.push_back(BfCompetition::ITA_Serie_A);
    marketFilter.m_competitionIds.push_back(BfCompetition::GBR_Barclays_Premier_League); // ??
    marketFilter.m_competitionIds.push_back(BfCompetition::FRA_Ligue_1_Orange);
    marketFilter.m_competitionIds.push_back(BfCompetition::DEU_Bundesliga_1);
    marketFilter.m_competitionIds.push_back(BfCompetition::AUT_Austrian_Bundesliga);
    marketFilter.m_competitionIds.push_back(BfCompetition::GBR_League_One); // ??
    marketFilter.m_competitionIds.push_back(BfCompetition::GBR_League_Two); // ??
    marketFilter.m_competitionIds.push_back(BfCompetition::NLD_Eredivisie); // ??
    marketFilter.m_competitionIds.push_back(BfCompetition::ARG_Argentinian_Primera_Division);
    marketFilter.m_competitionIds.push_back(BfCompetition::COL_Colombian_Primera_A);
    marketFilter.m_competitionIds.push_back(BfCompetition::BOL_Bolivian_Liga_Nacional_A);
    marketFilter.m_competitionIds.push_back(BfCompetition::FIN_Veikkausliiga);
    marketFilter.m_competitionIds.push_back(BfCompetition::NIC_Nicaraguan_Primera_Division);
    marketFilter.m_competitionIds.push_back(BfCompetition::PRT_Primeira_Liga);
    marketFilter.m_competitionIds.push_back(BfCompetition::URY_Uruguayan_Primera);

    // Cup
    marketFilter.m_competitionIds.push_back(BfCompetition::FIN_Finnish_Cup);

    // Odd
    marketFilter.m_competitionIds.push_back(BfCompetition::JPN_J_League);
    marketFilter.m_competitionIds.push_back(BfCompetition::ECU_Ecuadorian_Primera_A);
    marketFilter.m_competitionIds.push_back(BfCompetition::CHE_Swiss_Super_League);

    // Second national legue

    marketFilter.m_competitionIds.push_back(BfCompetition::DEU_Bundesliga_2);
    marketFilter.m_competitionIds.push_back(BfCompetition::FRA_Ligue_2_Orange);
    marketFilter.m_competitionIds.push_back(BfCompetition::DNK_Danish_Division_1);
    marketFilter.m_competitionIds.push_back(BfCompetition::ESP_Segunda_Division);
    marketFilter.m_competitionIds.push_back(BfCompetition::ITA_Serie_B);
    marketFilter.m_competitionIds.push_back(BfCompetition::NOR_Tippeligaen);

    marketFilter.m_competitionIds.push_back(BfCompetition::ARG_Argentinian_Primera_B_Nacional);
    marketFilter.m_competitionIds.push_back(BfCompetition::ARG_Argentinian_Primera_B_Metropolitana);
    marketFilter.m_competitionIds.push_back(BfCompetition::AUT_Austrian_Regionalliga);
    marketFilter.m_competitionIds.push_back(BfCompetition::BEL_Belgian_Second_Division);
    marketFilter.m_competitionIds.push_back(BfCompetition::CHE_Swiss_Super_League);
    marketFilter.m_competitionIds.push_back(BfCompetition::COL_Colombian_Primera_B);
    marketFilter.m_competitionIds.push_back(BfCompetition::CZE_Czech_2_Liga);
    marketFilter.m_competitionIds.push_back(BfCompetition::EGY_Egyptian_Premier);
    marketFilter.m_competitionIds.push_back(BfCompetition::GBR_The_Championship);

    // Asian
    marketFilter.m_competitionIds.push_back(BfCompetition::IDN_Indonesian_Cup);
    marketFilter.m_competitionIds.push_back(BfCompetition::JPN_J_League);
*/
    //marketFilter.m_competitionIds = BfCompetition::oneList();
    //marketFilter.m_competitionIds.push_back(BfCompetition::ALL);

    return marketFilter;
  }

  static std::pair<BetfairMarketFilter, std::list<BfMarketProjection::Enum> > getMarketCatalogueFilter(QString eventId) {
    BetfairMarketFilter marketFilter;
    marketFilter.m_eventIds.push_back(eventId);

    marketFilter.m_marketBettingTypes.push_back(BfMarketType::MATCH_ODDS);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::CORRECT_SCORE);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::CORRECT_SCORE2);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::TOTAL_GOALS);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_05);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_15);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_25);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_35);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_45);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_55);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_65);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_75);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::OVER_UNDER_85);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::NEXT_GOAL);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::EXACT_GOALS);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::HALF_TIME);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::HALF_TIME_FULL_TIME);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::HALF_TIME_SCORE);
    marketFilter.m_marketBettingTypes.push_back(BfMarketType::ASIAN_HANDICAP);

    std::list<BfMarketProjection::Enum> marketProjections;
    marketProjections.push_back(BfMarketProjection::MARKET_DESCRIPTION);
    marketProjections.push_back(BfMarketProjection::RUNNER_DESCRIPTION);
    marketProjections.push_back(BfMarketProjection::EVENT);
    marketProjections.push_back(BfMarketProjection::COMPETITION);

    return std::make_pair<BetfairMarketFilter, std::list<BfMarketProjection::Enum> >(marketFilter, marketProjections);
  }
};

#endif // BFFILTERFACTORY_H

