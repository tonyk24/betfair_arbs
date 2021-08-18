#ifndef BFCURRENTORDERSTATUS_H
#define BFCURRENTORDERSTATUS_H

#ifndef BFEXECUTIONREPORTSTATUS_H
#define BFEXECUTIONREPORTSTATUS_H

#include <stdexcept>
#include <QString>

class BfExecutionReportStatus {
public:
  enum Enum {
    SUCCESS,
    FAILURE,
    PROCESSED_WITH_ERRORS,
    TIMEOUT
  };

  static Enum toEnum(const QString &str) {
    if (str == "SUCCESS") {
      return SUCCESS;
    } else if (str == "FAILURE") {
      return FAILURE;
    } else if (str == "PROCESSED_WITH_ERRORS") {
      return PROCESSED_WITH_ERRORS;
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
    } else if (t == PROCESSED_WITH_ERRORS) {
      return QString("PROCESSED_WITH_ERRORS");
    } else if (t == TIMEOUT) {
      return QString("TIMEOUT");
    }

    return QString("UNKOWN_BfExecutionReportStatus");
  }
};

#endif // BFEXECUTIONREPORTSTATUS_H



#endif // BFCURRENTORDERSTATUS_H

