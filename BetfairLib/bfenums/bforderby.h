#ifndef BFORDERBY_H
#define BFORDERBY_H

#include <stdexcept>
#include <QString>

class BfOrderBy {
public:
  enum Enum {
    BY_BET,
    BY_MARKET,
    BY_MATCH_TIME,
    BY_PLACE_TIME,
    BY_SETTLED_TIME,
    BY_VOID_TIME
  };

  static Enum toEnum(const QString &str) {
    if (str == "BY_BET") {
      return BY_BET;
    } else if (str == "BY_MARKET") {
      return BY_MARKET;
    } else if (str == "BY_MATCH_TIME") {
      return BY_MATCH_TIME;
    } else if (str == "BY_PLACE_TIME") {
      return BY_PLACE_TIME;
    } else if (str == "BY_SETTLED_TIME") {
      return BY_SETTLED_TIME;
    } else if (str == "BY_VOID_TIME") {
      return BY_VOID_TIME;
    }

    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == BY_BET) {
      return QString("BY_BET");
    } else if (t == BY_MARKET) {
      return QString("BY_MARKET");
    } else if (t == BY_MATCH_TIME) {
      return QString("BY_MATCH_TIME");
    } else if (t == BY_PLACE_TIME) {
      return QString("BY_PLACE_TIME");
    } else if (t == BY_SETTLED_TIME) {
      return QString("BY_SETTLED_TIME");
    } else if (t == BY_VOID_TIME) {
      return QString("BY_VOID_TIME");
    }

    return QString("UNKOWN_BfOrderByEnum");
  }
};

#endif // BFORDERBY_H

