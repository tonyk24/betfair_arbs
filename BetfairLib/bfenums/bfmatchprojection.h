#ifndef BFMATCHPROJECTION_H
#define BFMATCHPROJECTION_H

#include <stdexcept>
#include <QString>

class BfPriceProjection {
public:
  enum Enum { NO_ROLLUP,
              ROLLED_UP_BY_PRICE,
              ROLLED_UP_BY_AVG_PRICE };

  static Enum toEnum(const QString &str) {
    if (str == "NO_ROLLUP") {
      return NO_ROLLUP;
    } else if (str == "ROLLED_UP_BY_PRICE") {
      return ROLLED_UP_BY_PRICE;
    } else if (str == "ROLLED_UP_BY_AVG_PRICE") {
      return ROLLED_UP_BY_AVG_PRICE;
    }

    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == NO_ROLLUP) {
      return QString("NO_ROLLUP");
    } else if (t == ROLLED_UP_BY_PRICE) {
      return QString("ROLLED_UP_BY_PRICE");
    } else if (t == ROLLED_UP_BY_AVG_PRICE) {
      return QString("ROLLED_UP_BY_AVG_PRICE");
    }

    return QString("UNKNOWN_BfPriceProjectionEnum");
  }
};

#endif // BFMATCHPROJECTION_H

