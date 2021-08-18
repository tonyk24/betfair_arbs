#ifndef BFMARKETSTATUS_H
#define BFMARKETSTATUS_H

#include <stdexcept>
#include <QString>

class BfMarketStatus {
public:
  enum Enum {
    INACTIVE,
    OPEN,
    SUSPENDED,
    CLOSED
  };

  static Enum toEnum(const QString &str) {
    if (str == "INACTIVE") {
      return INACTIVE;
    } else if (str == "OPEN") {
      return OPEN;
    } else if (str == "SUSPENDED") {
      return SUSPENDED;
    } else if (str == "CLOSED") {
      return  CLOSED;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == INACTIVE) {
      return QString("INACTIVE");
    } else if (t == OPEN) {
      return QString("OPEN");
    } else if (t == SUSPENDED) {
      return QString("SUSPENDED");
    } else if (t == CLOSED) {
      return QString("CLOSED");
    }

    return QString("UNKOWN_BfMarketStatusEnum");
  }
};

#endif // BFMARKETSTATUS_H

