#ifndef EVENTDATAT_H
#define EVENTDATAT_H

#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"

using namespace BfLib;

class EventDataT {
public:
  EventDataT(const BfEvent &event,
             const QDateTime &dateTime,
             const std::list<BetfairMarket>& markets)
    : m_event(event),
      m_dateTime(dateTime),
      m_markets(markets){
  }

  bool hasMarketData() {
    bool hasData = m_markets.size() > 0;

    for (std::list<BetfairMarket>::iterator it = m_markets.begin();
         it != m_markets.end(); it++) {
      if (!hasData && it->hasSelectionData()) {
        hasData = true;
      }
    }

    return hasData;
  }

  BfEvent m_event;
  QDateTime m_dateTime;
  std::list<BetfairMarket> m_markets;
};

#endif // EVENTDATAT_H

