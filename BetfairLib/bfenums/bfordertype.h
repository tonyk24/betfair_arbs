#ifndef BFORDERTYPE_H
#define BFORDERTYPE_H

#include <stdexcept>
#include <QString>

class BfOrderType {
public:
  enum Enum {
    LIMIT,
    LIMIT_ON_CLOSE,
    MARKET_ON_CLOSE
  };

  static Enum toEnum(const QString &str) {
    if (str == "LIMIT") {
      return LIMIT;
    } else if (str == "LIMIT_ON_CLOSE") {
      return LIMIT_ON_CLOSE;
    } else if (str == "MARKET_ON_CLOSE") {
      return MARKET_ON_CLOSE;
    }

    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == LIMIT) {
      return QString("LIMIT");
    } else if (t == LIMIT_ON_CLOSE) {
      return QString("LIMIT_ON_CLOSE");
    } else if (t == MARKET_ON_CLOSE) {
      return QString("MARKET_ON_CLOSE");
    }

    return QString("UNKOWN_BfOrderTypeEnum");
  }
};

#endif // BFORDERTYPE_H

