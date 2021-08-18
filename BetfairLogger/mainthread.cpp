#include "mainthread.h"

#include "betcontrollerlib.h"
#include "misc/config.h"

MainThread::MainThread() {

}

void MainThread::quit() {
  bl->quit();
}


void MainThread::listEvents() {
  bl->sendListEvents();
}

void MainThread::listEventsDetail(int slot) {
  bl->sendListEventsDetailed(slot);
}

void MainThread::listEventsBets(int slot, int index) {
  bl->sendListEventsBets(slot, index);
}

void MainThread::listEventsBetsForMarket(int slot, int index, QString market) {
  if (market == "TG") {
    market = "Total Goals";
  } else {
    return;
  }
  bl->sendListEventsBets(slot, index, market);
}

void MainThread::listAccount() {
  bl->sendListAccount();
}

void MainThread::listEventDataConsumer() {
  bl->sendListEventDataConsumer();
}

void MainThread::listConfig() {
  bl->sendListConfig();
}

void MainThread::takeBet(QString eventId, qint64 selId, BfSide::Enum side) {
  bl->sendTakeBet(eventId, selId, side);
}

void MainThread::recDebugMsg(QString msg) {
  emit debugMessage(msg);
}

void MainThread::run(){
  try {
    qDebug() << "MainThread::run()";
    Config *config = new Config(true);
    bl = new BetControllerLib(0, config);

    connect(bl, SIGNAL(debugMsg(QString)),
            this, SLOT(recDebugMsg(QString)));

    bl->run();
  } catch(...) {
    qWarning() << "Received exception....";
  }
}

void MainThread::aboutToQuitApp() {

}
