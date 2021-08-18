#ifndef BFINSTRUCTIONREPORTSTATUS_H
#define BFINSTRUCTIONREPORTSTATUS_H

#include <stdexcept>
#include <QString>

class BfInstructionReportStatus {
public:
  enum Enum {
    SUCCESS,
    FAILURE,
    TIMEOUT
  };

  static Enum toEnum(const QString &str) {
    if (str == "SUCCESS") {
      return SUCCESS;
    } else if (str == "FAILURE") {
      return FAILURE;
    } else if (str == "TIMEOUT") {
      return TIMEOUT;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == SUCCESS) {
      return QString("SUCCESS");
    } else if (t == FAILURE) {
      return QString("FAILURE");
    } else if (t == TIMEOUT) {
      return QString("TIMEOUT");
    }

    return QString("UNKOWN_BfInstructionReportStatus");
  }
};

#endif // BFINSTRUCTIONREPORTSTATUS_H

