#include <QCoreApplication>
#include <QTimer>

#include "controller.h"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  Controller controller;

  // connect up the signals
  QObject::connect(&controller, SIGNAL(finished()),
           &app, SLOT(quit()));
  QObject::connect(&app, SIGNAL(aboutToQuit()),
           &controller, SLOT(aboutToQuitApp()));

  // This code will start the messaging engine in QT and in
  // 10ms it will start the execution in the MainClass.run routine;
  QTimer::singleShot(10, &controller, SLOT(run()));
  return app.exec();
}
