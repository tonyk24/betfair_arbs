#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <list>
#include <utility>
#include "betfairapi/httpjsonclient.h"

class Triple {
public:
  Triple(QString a, QString b, QString c)
    : m_a(a), m_b(b), m_c(c) {
  }
  public:
    QString m_a;
    QString m_b;
    QString m_c;
};

class Controller : public QObject {
  Q_OBJECT
public:
  Controller();
  ~Controller();

public slots:
  void run();

  void listCompetition();
  std::list<std::pair<QString, QString> > readCsvFile();
  void writeCSV(std::list<std::pair<QString, QString> >mergedList);
  void writeHeaderFile(std::list<std::pair<QString, QString> >mergedList);

  void aboutToQuitApp();

private slots:
  void replyFinish(QString answer);
signals:
  void finished();
private:
  HttpJsonClient m_httpJsonClient;
  std::list<std::pair<QString, QString> > csvList;
};


#endif // CONTROLLER_H

