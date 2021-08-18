#include <algorithm>

#include <QDebug>

#include "betting/eventstats.h"

void EventStats::updateStats(QString eventId,
                             std::list<BetfairMarket> markets) {
  BfMarketStatus::Enum bfMarketOU05 = BfMarketStatus::CLOSED;
  bool OU05Found = false;
  BfMarketStatus::Enum bfMarketOU15 = BfMarketStatus::CLOSED;
  bool OU15Found = false;
  BfMarketStatus::Enum bfMarketOU25 = BfMarketStatus::CLOSED;
  bool OU25Found = false;
  BfMarketStatus::Enum bfMarketOU35 = BfMarketStatus::CLOSED;
  bool OU35Found = false;
  BfMarketStatus::Enum bfMarketOU45 = BfMarketStatus::CLOSED;
  bool OU45Found = false;
  BfMarketStatus::Enum bfMarketOU55 = BfMarketStatus::CLOSED;
  bool OU55Found = false;
  BfMarketStatus::Enum bfMarketOU65 = BfMarketStatus::CLOSED;
  bool OU65Found = false;
  BfMarketStatus::Enum bfMarketOU75 = BfMarketStatus::CLOSED;
  bool OU75Found = false;
  BfMarketStatus::Enum bfMarketOU85 = BfMarketStatus::CLOSED;
  bool OU85Found = false;
  BfMarketStatus::Enum bfMarketOU95 = BfMarketStatus::CLOSED;
  bool OU95Found = false;
  BfMarketStatus::Enum bfMarketOU105 = BfMarketStatus::CLOSED;
  bool OU105Found = false;

  for (std::list<BetfairMarket>::iterator itMarket = markets.begin();
       itMarket != markets.end(); itMarket++) {

    //qDebug() << "EventId= " << eventId
    //         << ", name= " << itMarket->m_marketName
    //         << ", status= " << BfMarketStatus::toStr(itMarket->m_marketStatus);

    // Each time MO market status is INACTIVE,OPEN or SUSPENDED, save date&time
    if (itMarket->m_marketName == "Match Odds") {
      if (itMarket->m_marketStatus == BfMarketStatus::INACTIVE ||
          itMarket->m_marketStatus == BfMarketStatus::OPEN ||
          itMarket->m_marketStatus == BfMarketStatus::SUSPENDED) {
        m_lastReceivedOpenMoMarketData[eventId] = QDateTime::currentDateTimeUtc();
      }

      // First time MO market status is CLOSED, save date&time
      if(itMarket->m_marketStatus == BfMarketStatus::CLOSED &&
         m_firstReceivedMOMarketClosed.find(eventId) == m_firstReceivedMOMarketClosed.end()) {
        m_firstReceivedMOMarketClosed[eventId] = QDateTime::currentDateTimeUtc();
      }
    } else if (itMarket->m_marketName == "Over/Under 0.5 Goals") {
      bfMarketOU05 = itMarket->m_marketStatus;
      OU05Found = true;
    } else if (itMarket->m_marketName == "Over/Under 1.5 Goals") {
      bfMarketOU15 = itMarket->m_marketStatus;
      OU15Found = true;
    } else if (itMarket->m_marketName == "Over/Under 2.5 Goals") {
      bfMarketOU25 = itMarket->m_marketStatus;
      OU25Found = true;
    } else if (itMarket->m_marketName == "Over/Under 3.5 Goals") {
      bfMarketOU35 = itMarket->m_marketStatus;
      OU35Found = true;
    } else if (itMarket->m_marketName == "Over/Under 4.5 Goals") {
      bfMarketOU45 = itMarket->m_marketStatus;
      OU45Found = true;
    } else if (itMarket->m_marketName == "Over/Under 5.5 Goals") {
      bfMarketOU55 = itMarket->m_marketStatus;
      OU55Found = true;
    } else if (itMarket->m_marketName == "Over/Under 6.5 Goals") {
      bfMarketOU65 = itMarket->m_marketStatus;
      OU65Found = true;
    } else if (itMarket->m_marketName == "Over/Under 7.5 Goals") {
      bfMarketOU75 = itMarket->m_marketStatus;
      OU75Found = true;
    } else if (itMarket->m_marketName == "Over/Under 8.5 Goals") {
      bfMarketOU85 = itMarket->m_marketStatus;
      OU85Found = true;
    } else if (itMarket->m_marketName == "Over/Under 9.5 Goals") {
      bfMarketOU95 = itMarket->m_marketStatus;
      OU95Found = true;
    } else if (itMarket->m_marketName == "Over/Under 10.5 Goals") {
      bfMarketOU105 = itMarket->m_marketStatus;
      OU105Found = true;
    }
  }

  m_totalGoalsEQ[eventId] = EventStats::TGEQ_UNKOWN;

  // Find TotalGoalsEq
  if (bfMarketOU05 != BfMarketStatus::CLOSED &&
      bfMarketOU05 != BfMarketStatus::SUSPENDED &&
      OU05Found) {
    //qDebug() << "OU05 found and open";
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_0;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      bfMarketOU15 != BfMarketStatus::CLOSED &&
      bfMarketOU15 != BfMarketStatus::SUSPENDED &&
      OU15Found) {
    //qDebug() << "OU15 found and open";
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_1;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      bfMarketOU25 != BfMarketStatus::CLOSED &&
      bfMarketOU25 != BfMarketStatus::SUSPENDED &&
      OU25Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_2;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      (bfMarketOU25 == BfMarketStatus::CLOSED || !OU25Found) &&
      bfMarketOU35 != BfMarketStatus::CLOSED &&
      bfMarketOU35 != BfMarketStatus::SUSPENDED &&
      OU35Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_3;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      (bfMarketOU25 == BfMarketStatus::CLOSED || !OU25Found)&&
      (bfMarketOU35 == BfMarketStatus::CLOSED || !OU35Found) &&
      bfMarketOU45 != BfMarketStatus::CLOSED &&
      bfMarketOU45 != BfMarketStatus::SUSPENDED &&
      OU45Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_4;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      (bfMarketOU25 == BfMarketStatus::CLOSED || !OU25Found)&&
      (bfMarketOU35 == BfMarketStatus::CLOSED || !OU35Found) &&
      (bfMarketOU45 == BfMarketStatus::CLOSED || !OU45Found) &&
      bfMarketOU55 != BfMarketStatus::CLOSED &&
      bfMarketOU55 != BfMarketStatus::SUSPENDED &&
      OU55Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_5;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      (bfMarketOU25 == BfMarketStatus::CLOSED || !OU25Found) &&
      (bfMarketOU35 == BfMarketStatus::CLOSED || !OU35Found) &&
      (bfMarketOU45 == BfMarketStatus::CLOSED || !OU45Found) &&
      (bfMarketOU55 == BfMarketStatus::CLOSED || !OU55Found) &&
      bfMarketOU65 != BfMarketStatus::CLOSED &&
      bfMarketOU65 != BfMarketStatus::SUSPENDED &&
      OU65Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_6;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      (bfMarketOU25 == BfMarketStatus::CLOSED || !OU25Found) &&
      (bfMarketOU35 == BfMarketStatus::CLOSED || !OU35Found) &&
      (bfMarketOU45 == BfMarketStatus::CLOSED || !OU45Found) &&
      (bfMarketOU55 == BfMarketStatus::CLOSED || !OU55Found) &&
      (bfMarketOU65 == BfMarketStatus::CLOSED || !OU65Found) &&
      bfMarketOU75 != BfMarketStatus::CLOSED &&
      bfMarketOU75 != BfMarketStatus::SUSPENDED &&
      OU75Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_7;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      (bfMarketOU25 == BfMarketStatus::CLOSED || !OU25Found) &&
      (bfMarketOU35 == BfMarketStatus::CLOSED || !OU35Found) &&
      (bfMarketOU45 == BfMarketStatus::CLOSED || !OU45Found) &&
      (bfMarketOU55 == BfMarketStatus::CLOSED || !OU55Found) &&
      (bfMarketOU65 == BfMarketStatus::CLOSED || !OU65Found) &&
      (bfMarketOU75 == BfMarketStatus::CLOSED || !OU75Found) &&
      bfMarketOU85 != BfMarketStatus::CLOSED &&
      bfMarketOU85 != BfMarketStatus::SUSPENDED &&
      OU85Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_8;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      (bfMarketOU25 == BfMarketStatus::CLOSED || !OU25Found) &&
      (bfMarketOU35 == BfMarketStatus::CLOSED || !OU35Found) &&
      (bfMarketOU45 == BfMarketStatus::CLOSED || !OU45Found) &&
      (bfMarketOU55 == BfMarketStatus::CLOSED || !OU55Found) &&
      (bfMarketOU65 == BfMarketStatus::CLOSED || !OU65Found) &&
      (bfMarketOU75 == BfMarketStatus::CLOSED || !OU75Found) &&
      (bfMarketOU85 == BfMarketStatus::CLOSED || !OU85Found) &&
      bfMarketOU95 != BfMarketStatus::CLOSED &&
      bfMarketOU95 != BfMarketStatus::SUSPENDED &&
      OU95Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_9;
  }
  if ((bfMarketOU05 == BfMarketStatus::CLOSED || !OU05Found) &&
      (bfMarketOU15 == BfMarketStatus::CLOSED || !OU15Found) &&
      (bfMarketOU25 == BfMarketStatus::CLOSED || !OU25Found) &&
      (bfMarketOU35 == BfMarketStatus::CLOSED || !OU35Found) &&
      (bfMarketOU45 == BfMarketStatus::CLOSED || !OU45Found) &&
      (bfMarketOU55 == BfMarketStatus::CLOSED || !OU55Found) &&
      (bfMarketOU65 == BfMarketStatus::CLOSED || !OU65Found) &&
      (bfMarketOU75 == BfMarketStatus::CLOSED || !OU75Found) &&
      (bfMarketOU85 == BfMarketStatus::CLOSED || !OU85Found) &&
      (bfMarketOU95 == BfMarketStatus::CLOSED || !OU95Found) &&
      bfMarketOU105 != BfMarketStatus::CLOSED &&
      bfMarketOU105 != BfMarketStatus::SUSPENDED &&
      OU105Found) {
    m_totalGoalsEQ[eventId] = EventStats::TGEQ_10;
  }

  // Find Total Goals LessEquals

  if (m_totalGoalsEQ.find(eventId) == m_totalGoalsEQ.end()) {
    //qDebug() << "Total Goals= UNKOWN";
  } else {
    //qDebug() << "TOtal Goals= " << m_totalGoalsEQ[eventId];
  }
}

void EventStats::startGettingEvent(QString eventId) {
  m_startGettingEvent[eventId] = QDateTime::currentDateTimeUtc();
}

void EventStats::stopGettingEvent(QString eventId) {
  m_stopGettingEvent.push_back(eventId);
  qDebug() << "m_stopGettingEvent.size()=" << QString::number(m_stopGettingEvent.size());
}

bool EventStats::hasStoppedGettingEvent(QString eventId) {
  return std::find(m_stopGettingEvent.begin(), m_stopGettingEvent.end(), eventId) != m_stopGettingEvent.end();
}

bool EventStats::subscribingEventMoreThan5MinutesAgo(QString eventId) {
  if (m_startGettingEvent.find(eventId) ==
      m_startGettingEvent.end()) {
    return false;
  }

  // eventId was subscribed for, for more than 5 minutes ago
  if (m_startGettingEvent[eventId]
      .secsTo(QDateTime::currentDateTimeUtc())
      > 5*60) {
    return true;
  }

  return false;
}

bool EventStats::marketMOOpen5MinutesAgo(QString eventId) {
  // Has a market for event been received
  if (m_lastReceivedOpenMoMarketData.find(eventId) ==
      m_lastReceivedOpenMoMarketData.end()) {
    return false;
  }

  // A market from eventId was receceived for more than 5 minutes ago
  if (m_lastReceivedOpenMoMarketData[eventId]
      .secsTo(QDateTime::currentDateTimeUtc())
      > 5*60) {
    return false;
  }

  // Less than 5 mintes ago
  return true;
}

bool EventStats::marketMOClosedFor1Minutes(QString eventId) {
  // Assume MO market not yet received
  if (m_firstReceivedMOMarketClosed.find(eventId) ==
      m_firstReceivedMOMarketClosed.end()) {
    return false;
  }

  // More than 5 minutes ago
  if (m_firstReceivedMOMarketClosed[eventId]
      .secsTo(QDateTime::currentDateTimeUtc())
      > 60) {
    return true;
  }

  // Less than 5 minutes ago
  return false;
}

EventStats::TOTALGOALS_EQ EventStats::getTotalGoalsEquals(const QString &eventId) {
  if (m_totalGoalsEQ.find(eventId) != m_totalGoalsEQ.end()) {
    return m_totalGoalsEQ[eventId];
  }

  return TGEQ_UNKOWN;
}

EventStats::TOTALGOALS_LE EventStats::getTotalGoalsLessEquals(const QString &eventId) {
  if (m_totalGoalsLE.find(eventId) != m_totalGoalsLE.end()) {
    return m_totalGoalsLE[eventId];
  }

  return TGLE_UNKOWN;
}

void EventStats::reportEventError(QString eventId) {
  if (m_eventErrors.find(eventId) == m_eventErrors.end()) {
    m_eventErrors[eventId] = 0;
  }
  else  {
    m_eventErrors[eventId]++;
  }
}

unsigned int EventStats::hasEventError(QString eventId) {
  if (m_eventErrors.find(eventId) == m_eventErrors.end())
  {
    return 0;
  }
  return m_eventErrors[eventId];
}
