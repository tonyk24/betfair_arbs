#ifndef BFEVENT_H
#define BFEVENT_H

#include <QString>
#include <QDateTime>

#include "bfenums/bfcompetition.h"

class BfEvent
{
public:
  BfEvent(QString eventId,
               QString name,
               QString countryCode,
               QString timeZone,
               QString openDate):
    m_eventId(eventId),
    m_name(name),
    m_countryCode(countryCode),
    m_timeZone(timeZone),
    m_competition(BfCompetition::UNKOWN)
    // 2015-05-16T17:30:00.000Z
    //m_openDate(QDateTime::fromString(openDate, QString("yyyy-MM-ddThh:mm:ss.zzzZ")))
  {
    m_openDate = QDateTime::fromString(openDate, Qt::ISODate);
    m_openDate.setTimeSpec(Qt::UTC);
  }

  QString m_eventId;
  QString m_name;
  QString m_countryCode;
  QString m_timeZone;
  BfCompetition::Competition m_competition;
  QDateTime m_openDate;
};

#endif // BFEVENT_H

