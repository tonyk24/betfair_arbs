#include "eventdataconsumer.h"

EventDataConsumer::EventDataConsumer() : m_quit(false) {
  qDebug() << "EventDataConsumer()";
}

void EventDataConsumer::push(const BfEvent &event,
                             const std::list<BetfairMarket> &markets) {
  try {
    eventDataMutex.lock();
    if (std::find(m_eventsToNotLog.begin(), m_eventsToNotLog.end(), event.m_eventId) == m_eventsToNotLog.end()) {
      m_eventDataQueue[event.m_eventId]
          .push_back(EventDataT(event,
                                QDateTime::currentDateTimeUtc(),
                                markets));
    }
    eventDataMutex.unlock();
  } catch(...) {
    emit threadError("Caught exception in EventDataConsumer::push");
  }
}

void EventDataConsumer::finish(const QString &eventId) {
  try {
    eventDataMutex.lock();
    m_finnishEvents.push_back(eventId);
    eventDataMutex.unlock();
  } catch(...) {
    emit threadError("Caught exception in EventDataConsumer::finish");
  }
}

void EventDataConsumer::abortEvent(const QString &eventId) {
  try {
    eventDataMutex.lock();
    m_eventDataQueue.erase(eventId);
    m_eventsToNotLog.remove(eventId);
    m_finnishEvents.remove(eventId);
    eventDataMutex.unlock();
  } catch(...) {
    emit threadError("Caught exception in EventDataConsumer::abortEvent");
  }
}

void EventDataConsumer::quit() {
  m_quit = true;
}

void EventDataConsumer::run() {
  try {
    while (!m_quit) {
      // Retrieve event data
      eventDataMutex.lock();

      EventDataQueueMapT eventDataQueue;
      handleEventDataQueue(eventDataQueue);

      std::list<QString> eventsToFinnish;
      handleEventsToFinish(eventsToFinnish);

      eventDataMutex.unlock();

      bool nothingToDo = true;
      // Send event data to log writer
      for (EventDataQueueMapIteratorT it = eventDataQueue.begin();
           it != eventDataQueue.end(); it++) {
        if (!it->second.empty()) {
          nothingToDo = false;

          m_eventDataLogger.writeEventData(it->second);
        }
      }
      for (std::list<QString>::iterator it = eventsToFinnish.begin();
           it != eventsToFinnish.end(); it++) {
        nothingToDo = false;
        emit debugMessage("m_eventDataLogger.eventFinnished(" + *it + ")");
        m_eventDataLogger.eventFinnished(*it);
      }

      if (nothingToDo) {
        // No data in event queue, so sleep for 50 ms
        QThread::msleep(50);
      }
    }
  } catch(...) {
    emit threadError("Caught exception in EventDataConsumer::run");
  }
}

void EventDataConsumer::handleEventDataQueue(EventDataQueueMapT &eventDataQueue) {
  bool foundDataToLog = false;
  for (EventDataQueueMapIteratorT eQit = m_eventDataQueue.begin();
       eQit != m_eventDataQueue.end(); eQit++) {
    if (eQit->second.size() > 100) {
      if (std::find(m_eventsToNotLog.begin(), m_eventsToNotLog.end(), eQit->first) == m_eventsToNotLog.end()) {
        // More then 100 queing items, don't log (not enough resources)
        // Don't log event anymore
        m_eventsToNotLog.push_back(eQit->first);
        debugMessage("EventDataConsumer: Not logging event: " + eQit->first);
        eQit->second.clear();
      }
    } else if (!foundDataToLog && eQit->second.size() > 10) {
      // Should be size > 0 && size < 2000, and no other items for logging
      if (std::find(m_eventsToNotLog.begin(), m_eventsToNotLog.end(), eQit->first) == m_eventsToNotLog.end()) {
        foundDataToLog = true;
        eventDataQueue[eQit->first] = eQit->second;
        eQit->second.clear();
      }
    }
  }
}

void EventDataConsumer::handleEventsToFinish(std::list<QString> &eventsToFinnish) {
  for (std::list<QString>::iterator itEvent = m_finnishEvents.begin();
       itEvent != m_finnishEvents.end(); ) {
    if (std::find(m_eventsToNotLog.begin(), m_eventsToNotLog.end(), *itEvent) != m_eventsToNotLog.end()) {
      itEvent = m_finnishEvents.erase(itEvent);
    }
    // Only finnish when there is no data to write in the queue
    EventDataQueueMapIteratorT eventQueueIt = m_eventDataQueue.find(*itEvent);
    if (eventQueueIt == m_eventDataQueue.end()) {
      eventsToFinnish.push_back(*itEvent);
      itEvent = m_finnishEvents.erase(itEvent);
    } else if (m_eventDataQueue[*itEvent].empty()) {
      // Remove from eventQueue
      m_eventDataQueue.erase(eventQueueIt);
      eventsToFinnish.push_back(*itEvent);
      itEvent = m_finnishEvents.erase(itEvent);
      break;
    } else {
      itEvent++;
    }
  }
}
