#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QLocale>
#include <QtGlobal>
#include <QTimer>
#include <QDebug>

#include "mainthread.h"
#include "interactiveapp.h"
#include "misc/config.h"
#include "debugmsglogger.h"

DebugMsgLogger *debugMsgLogger = 0;
QMutex g_mutex;


void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & str)
{
  g_mutex.lock();
  debugMsgLogger->log(type, str);
  g_mutex.unlock();
}

int main(int argc, char *argv[])
{
  int ret = 0;
  try {
    debugMsgLogger = new DebugMsgLogger(0);
    debugMsgLogger->start();
    QLocale::setDefault(QLocale::English);
    QCoreApplication app(argc, argv);
    qInstallMessageHandler(myMessageHandler);

    InteractiveApp inter(0);

    // connect up the signals
    QObject::connect(&inter, SIGNAL(finished()),
                     &app, SLOT(quit()));

    // This code will start the messaging engine in QT and in
    // 10ms it will start the execution in the MainClass.run routine;
    QTimer::singleShot(10, &inter, SLOT(run()));
    ret = app.exec();
  } catch(const std::bad_alloc &ex) {
    qWarning() << "Caught exception std::bad_alloc: " << ex.what();
  }
  catch(std::exception ex) {
    qWarning() << "Caught std::exception: " << ex.what();
  }

  catch(...) {
    qWarning() << "Caught unknown exception";
  }

  delete debugMsgLogger;

  return ret;
}
