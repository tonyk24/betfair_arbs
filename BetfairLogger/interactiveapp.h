#ifndef INTERACTIVEAPP_H
#define INTERACTIVEAPP_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QStringList>
#include <QString>

#include "mainthread.h"
#include "misc/sleeper.h"

class InteractiveApp : public QObject {
    Q_OBJECT
public:
    InteractiveApp(QObject *parent) {
      Q_UNUSED(parent)
    }

private:
    QString m_incomingMsg;
    Sleeper m_sleeper;

private slots:
    void recDebugMsg(QString msg) {
      m_incomingMsg += msg;
    }

public slots:
  void quit() {

  }


  void run() {
    QTextStream tsOut( stdout );

    qDebug() << "InteractiveApp::run()";

    MainThread mainThread;

    connect(&mainThread, SIGNAL(debugMessage(QString)),
            this, SLOT(recDebugMsg(QString)));

    mainThread.start();

    bool quit = false;
    while (!quit) {
      QTextStream cin(stdin, QIODevice::ReadOnly);
      QTextStream cout(stdout, QIODevice::WriteOnly);
      QTextStream cerr(stderr, QIODevice::WriteOnly);

      QString str;
      cout << "Commands:" <<endl;
      cout << "* events" <<endl;
      cout << "* markets_<nr>" << endl;
      cout << "* bets_<slotnr>_<indexnr>" << endl;
      cout << "* betsm_<slotnr>_<indexnr>_<market>" << endl;
      cout << "* account" <<endl;
      cout << "* dataconsumer" <<endl;
      cout << "* config" <<endl;
      cout << "* statstg" << endl;
      cout << "* take_<event>_<sel>_<back/lay>" << endl;
      cout << "* quit" << endl;

      cin>>str;//
      if (str == "events") {
        m_incomingMsg = "";
        mainThread.listEvents();
        cout << waitForRsp() << endl;
      }
      else if (str.startsWith("markets")) {
        QStringList sl = str.split("_");
        if (sl.size() == 2) {
          m_incomingMsg = "";
          QString s = sl.at(1);
          mainThread.listEventsDetail(s.toInt());
          cout << waitForRsp() << endl;
        } else {
          cout << "Not enough args provided.." << str << endl;
        }
      }
      else if (str.startsWith("bets_")) {
        QStringList sl = str.split("_");
        if (sl.size() == 3) {
          m_incomingMsg = "";
          QString slot = sl.at(1);
          QString index = sl.at(2);
          mainThread.listEventsBets(slot.toInt(), index.toInt());
          cout << waitForRsp() << endl;
        } else {
          cout << "Not enough args provided.." << str << endl;
        }
      }
      else if (str.startsWith("betsm_")) {
        QStringList sl = str.split("_");
        if (sl.size() == 4) {
          m_incomingMsg = "";
          QString slot = sl.at(1);
          QString index = sl.at(2);
          QString market = sl.at(3);
          mainThread.listEventsBetsForMarket(slot.toInt(), index.toInt(), market);
          cout << waitForRsp() << endl;
        } else {
          cout << "Not enough args provided.." << str << endl;
        }
      }
      else if (str == "account") {
        m_incomingMsg = "";
        mainThread.listAccount();
        cout << waitForRsp() << endl;
      } else if (str == "dataconsumer") {
        m_incomingMsg = "";
        mainThread.listEventDataConsumer();
        cout << waitForRsp() << endl;
      }else if (str == "config") {
        m_incomingMsg = "";
        mainThread.listConfig();
        cout << waitForRsp() << endl;
      } else if (str == "statstg") {
        m_incomingMsg = "";
        // TODO
        cout << waitForRsp() << endl;
      }
      else if (str.startsWith("take_")) {
        QStringList sl = str.split("_");
        if (sl.size() == 4) {
          m_incomingMsg = "";
          /// <event>_<sel>_<back/lay>
          QString event = sl.at(1);
          QString sel = sl.at(2);
          QString backlay = sl.at(3);
          if (backlay == "back") {
            mainThread.takeBet(event, qint64(sel.toDouble()), BfSide::BACK);
          } else if (backlay == "lay") {
            mainThread.takeBet(event, qint64(sel.toDouble()), BfSide::LAY);
          } else {
            continue;
          }
          cout << waitForRsp() << endl;
        } else {
          cout << "Not enough args provided.." << str << endl;
        }
      }
      else if (str == "quit") {
        mainThread.quit();
        quit = true;
      } else {
        cout << "Unkown command: " << str << endl;
        m_sleeper.sleep(500);

      }
      cout.flush();//cout.flush()
    }

    mainThread.wait();
    emit finished();
  }

  QString waitForRsp() {
    QElapsedTimer timer;
    timer.start();
    qint64 lastTime = timer.elapsed();
    while (timer.elapsed() - lastTime < 3*1000) {
      QCoreApplication::processEvents();
    }

    return m_incomingMsg;
  }

signals:
  void aboutToQuit();
  void finished();
};

#endif // INTERACTIVEAPP_H

