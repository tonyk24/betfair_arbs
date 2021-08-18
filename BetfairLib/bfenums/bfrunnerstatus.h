#ifndef BFRUNNERSTATUS_H
#define BFRUNNERSTATUS_H

#include <stdexcept>
#include <QString>

class BfRunnerStatus {
public:
  enum Enum {
    ACTIVE,
    WINNER,
    LOSER,
    REMOVED_VACANT,
    REMOVED,
    HIDDEN
  };

  static Enum toEnum(const QString &str) {
    if (str == "ACTIVE") {
      return ACTIVE;
    } else if (str == "WINNER") {
      return WINNER;
    } else if (str == "LOSER") {
      return LOSER;
    } else if (str == "REMOVED_VACANT") {
      return REMOVED_VACANT;
    } else if (str == "REMOVED") {
      return REMOVED;
    } else if (str == "HIDDEN") {
      return HIDDEN;
    }

    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == ACTIVE) {
      return QString("ACTIVE");
    } else if (t == WINNER) {
      return QString("WINNER");
    } else if (t == LOSER) {
      return QString("LOSER");
    } else if (t == REMOVED_VACANT) {
      return QString("REMOVED_VACANT");
    } else if (t == REMOVED) {
      return QString("REMOVED");
    } else if (t == HIDDEN) {
      return QString("HIDDEN");
    }
    return QString("UNKOWN_BfRunnerStatusEnum");
  }
};

#endif // BFRUNNERSTATUS_H

