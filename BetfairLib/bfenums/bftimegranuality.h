#ifndef BFTIMEGRANUALITY_H
#define BFTIMEGRANUALITY_H

#include <stdexcept>
#include <QString>

class BfTimeGranuality {
public:
  enum Enum {
    DAYS,
    HOURS,
    MINUTES
  };

  static Enum toEnum(const QString &str) {
    if (str == "DAYS") {
      return DAYS;
    } else if(str == "HOURS") {
      return HOURS;
    } else if (str == "MINUTES") {
      return MINUTES;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == DAYS) {
      return QString("DAYS");
    } else if (t == HOURS) {
      return QString("HOURS");
    } else if (t == MINUTES) {
      return QString("MINUTES");
    }

    return QString("BfTimeGranualityEnum");
  }
};

#endif // BFTIMEGRANUALITY_H

