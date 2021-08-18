#ifndef BETFAIRMARKETFILTER_H
#define BETFAIRMARKETFILTER_H

#include <list>
#include <QDateTime>
#include <QtDebug>

#include "bfenums/bfcompetition.h"
#include "betfairfilter/bfmarkettype.h"

class BetfairMarketFilter {
public:
  BetfairMarketFilter():
    m_startAfter(0),
    m_startBefore(0),
    m_maxResults(100)
  {
  }

  ~BetfairMarketFilter() {
    if (m_startAfter != 0) {
      delete m_startAfter;
      m_startAfter = 0;
    }
    if (m_startBefore != 0) {
      delete m_startBefore;
      m_startBefore = 0;
    }
  }

  BetfairMarketFilter( const BetfairMarketFilter &obj):
    m_competitionIds (obj.m_competitionIds),
    m_eventIds (obj.m_eventIds),
    m_eventTypeIds(obj.m_eventTypeIds),
    m_marketBettingTypes(obj.m_marketBettingTypes),
    m_maxResults(obj.m_maxResults)
   {
    if (obj.m_startAfter != 0) {
      m_startAfter = new QDateTime(*obj.m_startAfter);
    } else {
      m_startAfter = 0;
    }
    if (obj.m_startBefore != 0) {
        m_startBefore = new QDateTime(*obj.m_startBefore);
    } else {
      m_startBefore = 0;
    }
  }


  BetfairMarketFilter& operator=(const BetfairMarketFilter& obj)
  {
    if (obj.m_startAfter != 0) {
      m_startAfter = new QDateTime(*obj.m_startAfter);
    } else {
      m_startAfter = 0;
    }
    if (obj.m_startBefore != 0) {
      m_startBefore = new QDateTime(*obj.m_startBefore);
    } else {
      m_startBefore = 0;
    }
    m_competitionIds = obj.m_competitionIds;
    m_eventIds = obj.m_eventIds;
    m_eventTypeIds = obj.m_eventTypeIds;
    m_marketBettingTypes = obj.m_marketBettingTypes;
    m_maxResults = obj.m_maxResults;

    return *this;
  }

  std::list<QString> m_competitionIds;
  std::list<QString> m_eventIds;
  std::list<QString> m_eventTypeIds;
  std::list<BfMarketType::Type> m_marketBettingTypes;

  QDateTime *m_startAfter;
  QDateTime *m_startBefore;

  int m_maxResults;
};

#endif // BETFAIRMARKETFILTER_H

