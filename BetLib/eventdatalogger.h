#ifndef EVENTDATALOGGER_H
#define EVENTDATALOGGER_H

#include <list>
#include <map>

#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>

#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"
#include "eventdatat.h"

class EventDataLogger : public QObject {
  Q_OBJECT
public:
  EventDataLogger(QObject *parent=0);
  void createDirectories();

  void writeEventData(const std::list<EventDataT> &eventData);
  void eventFinnished(const QString &eventId);

  QString doubleToStr(const std::vector<double> &dvec,
                             unsigned int index) {
    if (dvec.size() > index) {
      return QString::number(dvec[index]);
    }

    return "-1";
  }

  const QString m_dataDirStr;
  const QString m_tempDirStr;
  const QString m_destinationDirStr;

  QDir m_tempDir;
  QDir m_destDir;

private:
  std::map<QString, QFile*> m_eventMarketLogFile;
signals:
  void debugMessage(QString msg);
};

#endif // EVENTDATALOGGER_H

