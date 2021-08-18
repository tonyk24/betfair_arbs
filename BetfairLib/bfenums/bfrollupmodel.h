#ifndef BFROLLUPMODEL_H
#define BFROLLUPMODEL_H

#include <stdexcept>
#include <QString>

class BfRollupModel {
public:
  enum Enum {
    STAKE,
    PAYOUT,
    MANAGED_LIABILITY,
    NONE
  };

  static Enum toEnum(const QString &str) {
    if (str == "STAKE") {
      return STAKE;
    } else if (str == "PAYOUT") {
      return PAYOUT;
    } else if (str == "MANAGED_LIABILITY") {
      return MANAGED_LIABILITY;
    } else if (str == "NONE") {
      return NONE;
    }

    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == STAKE) {
      return QString("STAKE");
    } else if (t == PAYOUT) {
      return QString("PAYOUT");
    } else if (t == MANAGED_LIABILITY) {
      return QString("MANAGED_LIABILITY");
    } else if (t == NONE) {
      return QString("NONE");
    }

    return QString("UNKOWN_BfRollupModel");
  }
};

#endif // BFROLLUPMODEL_H

