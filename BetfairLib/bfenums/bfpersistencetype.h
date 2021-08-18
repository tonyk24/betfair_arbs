#ifndef BFPERSISTENCETYPE_H
#define BFPERSISTENCETYPE_H

#include <stdexcept>
#include <QString>

class BfPersistenceType {
public:
  enum Enum {
    LAPSE,
    PERSIST,
    MARKET_ON_CLOSE
  };

  static Enum toEnum(const QString &str) {
    if (str == "LAPSE") {
      return LAPSE;
    } else if (str == "PERSIST") {
      return PERSIST;
    } else if (str == "MARKET_ON_CLOSE") {
      return MARKET_ON_CLOSE;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == LAPSE) {
      return QString("LAPSE");
    } else if (t == PERSIST) {
      return QString("PERSIST");
    } else if (t == MARKET_ON_CLOSE) {
      return QString("MARKET_ON_CLOSE");
    }

    return QString("UNKOWN_BfPersistenceType");
  }
};

#endif // BFPERSISTENCETYPE_H

