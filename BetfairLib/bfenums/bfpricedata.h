#ifndef BFPRICEDATA_H
#define BFPRICEDATA_H

#include <stdexcept>
#include <QString>

class BfPriceData {
public:
  enum Enum { SP_AVAILABLE,
              SP_TRADED,
              EX_BEST_OFFERS,
              EX_ALL_OFFERS,
              EX_TRADED };

  static Enum toEnum(const QString &str) {
    if (str == "SP_AVAILABLE") {
      return SP_AVAILABLE;
    } else if (str == "SP_TRADED") {
      return SP_TRADED;
    } else if (str == "EX_BEST_OFFERS") {
      return EX_BEST_OFFERS;
    } else if (str == "EX_ALL_OFFERS") {
      return EX_ALL_OFFERS;
    } else if (str == "EX_TRADED") {
      return EX_TRADED;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == SP_AVAILABLE) {
      return QString("SP_AVAILABLE");
    } else if (t == SP_TRADED) {
      return QString("SP_TRADED");
    } else if (t == EX_BEST_OFFERS) {
      return QString("EX_BEST_OFFERS");
    } else if (t == EX_ALL_OFFERS) {
      return QString("EX_ALL_OFFERS");
    } else if (t == EX_TRADED) {
      return QString("EX_TRADED");
    }

    return QString("UNKNOWN_BfPriceDataEnum");
  }

};

#endif // BFPRICEDATA_H

