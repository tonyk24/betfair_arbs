#ifndef BFSORTDIR_H
#define BFSORTDIR_H

#include <stdexcept>
#include <QString>

class BfSortDir {
public:
  enum Enum { EARLIEST_TO_LATEST,
              LATEST_TO_EARLIEST };

  static Enum toEnum(const QString &str) {
    if (str == "EARLIEST_TO_LATEST") {
      return EARLIEST_TO_LATEST;
    } else if (str == LATEST_TO_EARLIEST) {
      return LATEST_TO_EARLIEST;
    }

    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == EARLIEST_TO_LATEST) {
      return QString("EARLIEST_TO_LATEST");
    } else if (t == LATEST_TO_EARLIEST) {
      return QString("LATEST_TO_EARLIEST");
    }

    return QString("UNKOWN_BfSortDirEnum");
  }
};

#endif // BFSORTDIR_H

