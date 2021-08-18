#ifndef EVENTDATACONSUMER_H
#define EVENTDATACONSUMER_H

#include <QThread>
#include <QMutex>
#include <QDateTime>
#include <QString>
#include <list>
#include <map>

#include "eventdatalogger.h"
#include "bftypes/bfevent.h"
#include "eventdatat.h"

using namespace BfLib;

class EventDataConsumer : public QThread {
  Q_OBJECT
public:
  typedef std::map<QString, std::list<EventDataT> > EventDataQueueMapT;
  typedef std::map<QString, std::list<EventDataT> >::iterator EventDataQueueMapIteratorT;

  EventDataConsumer();

  void push(const BfEvent &event,
            const std::list<BetfairMarket> &markets);

  void finish(const QString &eventId);
  void abortEvent(const QString &eventId);

  void quit();

  void run();

private:
  // From run
  void handleEventDataQueue(EventDataQueueMapT &eventDataQueue);
  void handleEventsToFinish(std::list<QString> &eventsToFinnish);
  bool m_quit;

  QMutex eventDataMutex;

  EventDataQueueMapT m_eventDataQueue;
  std::list<QString> m_eventsToNotLog;
  std::list<QString> m_finnishEvents;

  EventDataLogger m_eventDataLogger;
signals:
  void threadError(QString errormsg);
  void debugMessage(QString msg);
};

#endif // EVENTDATACONSUMER_H

