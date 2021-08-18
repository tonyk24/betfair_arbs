#ifndef BFSIDE_H
#define BFSIDE_H

#include <stdexcept>
#include <QString>

class BfSide {
public:
  enum Enum {
    BACK,
    LAY };

  static Enum toEnum(const QString &str) {
    if (str == "BACK") {
      return BACK;
    } else if ("LAY") {
      return LAY;
    }

    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == BACK) {
      return QString("BACK");
    } else if (t == LAY) {
      return QString("LAY");
    }

    return QString("UNKOWN_BfSideEnum");
  }
};

#endif // BFSIDE_H

