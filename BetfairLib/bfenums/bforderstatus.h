#ifndef BFORDERSTATUS_H
#define BFORDERSTATUS_H

#include <stdexcept>
#include <QString>

class BfOrderStatus {
public:
  enum Enum {
    EXECUTION_COMPLETE,
    EXECUTABLE,
    PENDING,
    EXPIRED
  };

  static Enum toEnum(const QString &str) {
    if (str == "EXECUTION_COMPLETE") {
      return EXECUTION_COMPLETE;
    } else if (str == "EXECUTABLE") {
      return EXECUTABLE;
    }else if (str == "PENDING") {
      return PENDING;
    }else if (str == "EXPIRED") {
      return EXPIRED;
    }


    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == EXECUTION_COMPLETE) {
      return QString("EXECUTION_COMPLETE");
    } else if (t == EXECUTABLE) {
      return QString("EXECUTABLE");
    } else if (t == PENDING) {
      return QString("PENDING");
    } else if (t == EXPIRED) {
      return QString("EXPIRED");
    }

    return QString("UNKOWN_BfOrderStatusEnum");
  }
};

#endif // BFORDERSTATUS_H

