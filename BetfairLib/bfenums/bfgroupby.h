#ifndef BFGROUPBY_H
#define BFGROUPBY_H

#include <stdexcept>
#include <QString>

class BfGroupBy {
public:
  enum Enum {
    EVENT_TYPE,
    EVENT,
    MARKET,
    SIDE,
    BET
  };

  static Enum toEnum(const QString &str) {
    if (str == "EVENT_TYPE") {
      return EVENT_TYPE;
    } else if (str == "EVENT") {
      return EVENT;
    } else if (str == "MARKET") {
      return MARKET;
    } else if (str == "SIDE") {
      return SIDE;
    } else if (str == "BET") {
      return BET;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == EVENT_TYPE) {
      return QString("EVENT_TYPE");
    } else if (t == EVENT) {
      return QString("EVENT");
    } else if (t == MARKET) {
      return QString("MARKET");
    } else if (t == SIDE) {
      return QString("SIDE");
    } else if (t == BET) {
      return QString("BET");
    }

    return QString("UNKOWN_BfGroupByEnum");
  }
};

#endif // BFGROUPBY_H

