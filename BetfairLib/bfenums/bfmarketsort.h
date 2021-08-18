#ifndef BFMARKETSORT_H
#define BFMARKETSORT_H

#include <stdexcept>
#include <QString>

class BfMarketSort {
public:
  enum Enum {
    MINIMUM_TRADED,
    MAXIMUM_TRADED,
    MINIMUM_AVAILABLE,
    MAXIMUM_AVAILABLE,
    FIRST_TO_START,
    LAST_TO_START };

  static Enum toEnum(const QString &str) {
    if (str == "MINIMUM_TRADED") {
      return MINIMUM_TRADED;
    } else if(str == "MAXIMUM_TRADED") {
      return MAXIMUM_TRADED;
    } else if (str == "MINIMUM_AVAILABLE") {
      return MINIMUM_AVAILABLE;
    } else if (str == "MAXIMUM_AVAILABLE") {
      return MAXIMUM_AVAILABLE;
    } else if (str == "FIRST_TO_START") {
      return FIRST_TO_START;
    } else if (str == "LAST_TO_START") {
      return LAST_TO_START;
    }

    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == MINIMUM_TRADED) {
      return QString("MINIMUM_TRADED");
    } else if (t == MAXIMUM_TRADED) {
      return QString("MAXIMUM_TRADED");
    } else if (t == MINIMUM_AVAILABLE) {
      return QString("MINIMUM_AVAILABLE");
    } else if (t == MAXIMUM_AVAILABLE) {
      return QString("MAXIMUM_AVAILABLE");
    } else if (t == FIRST_TO_START) {
      return QString("FIRST_TO_START");
    } else if (t == LAST_TO_START) {
      return QString("LAST_TO_START");
    }

    return QString("UNKOWN_BfMarketSortEnum");
  }
};

#endif // BFMARKETSORT_H

