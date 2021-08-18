#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QThread>
#include <QMutex>
#include <QDateTime>
#include <QString>
#include <list>
#include <map>

#include "betcontrollerlib.h"

class MainThread : public QThread {
  Q_OBJECT
public:

  MainThread();

  void quit();

  void listEvents();
  void listEventsDetail(int slot);
  void listEventsBets(int slot, int index);
  void listEventsBetsForMarket(int slot, int index, QString market);
  void listAccount();
  void listEventDataConsumer();
  void listConfig();
  void takeBet(QString eventId, qint64 selId, BfSide::Enum side);

private:
  BetControllerLib *bl;
  bool m_quit;

signals:
  void threadError(QString errormsg);
  void debugMessage(QString msg);
public slots:
  void run();
  void aboutToQuitApp();
private slots:
  void recDebugMsg(QString msg);
};

#endif // MAINTHREAD_H

