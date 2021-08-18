#ifndef BFEXECUTIONREPORTERRORCODE_H
#define BFEXECUTIONREPORTERRORCODE_H

#include <QString>
#include <stdexcept>

class BfExecutionErrorReportCode {
public:
  enum Enum {
    NONE,
    ERROR_IN_MATCHER,
    PROCESSED_WITH_ERRORS,
    BET_ACTION_ERROR,
    INVALID_ACCOUNT_STATE,
    INVALID_WALLET_STATUS,
    INSUFFICIENT_FUNDS,
    LOSS_LIMIT_EXCEEDED,
    MARKET_SUSPENDED,
    MARKET_NOT_OPEN_FOR_BETTING,
    DUPLICATE_TRANSACTION,
    INVALID_ORDER,
    INVALID_MARKET_ID,
    PERMISSION_DENIED,
    DUPLICATE_BETIDS,
    NO_ACTION_REQUIRED,
    SERVICE_UNAVAILABLE,
    REJECTED_BY_REGULATOR
  };

  static Enum toEnum(const QString &str) {
    if (str == "ERROR_IN_MATCHER") {
      return ERROR_IN_MATCHER;
    } else if (str == "PROCESSED_WITH_ERRORS") {
      return PROCESSED_WITH_ERRORS;
    } else if (str == "BET_ACTION_ERROR") {
      return BET_ACTION_ERROR;
    } else if (str == "INVALID_ACCOUNT_STATE") {
      return INVALID_ACCOUNT_STATE;
    } else if (str == "INVALID_WALLET_STATUS") {
      return INVALID_WALLET_STATUS;
    } else if (str == "INSUFFICIENT_FUNDS") {
      return INSUFFICIENT_FUNDS;
    } else if (str == "LOSS_LIMIT_EXCEEDED") {
      return LOSS_LIMIT_EXCEEDED;
    } else if (str == "MARKET_SUSPENDED") {
      return MARKET_SUSPENDED;
    } else if (str == "MARKET_NOT_OPEN_FOR_BETTING") {
      return MARKET_NOT_OPEN_FOR_BETTING;
    } else if (str == "DUPLICATE_TRANSACTION") {
      return DUPLICATE_TRANSACTION;
    } else if (str == "INVALID_ORDER") {
      return INVALID_ORDER;
    } else if (str == "INVALID_MARKET_ID") {
      return INVALID_MARKET_ID;
    } else if (str == "PERMISSION_DENIED") {
      return PERMISSION_DENIED;
    } else if (str == "DUPLICATE_BETIDS") {
      return DUPLICATE_BETIDS;
    } else if (str == "NO_ACTION_REQUIRED") {
      return NO_ACTION_REQUIRED;
    } else if (str == "SERVICE_UNAVAILABLE") {
      return SERVICE_UNAVAILABLE;
    } else if (str == "REJECTED_BY_REGULATOR") {
      return REJECTED_BY_REGULATOR;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == ERROR_IN_MATCHER) {
      return QString("ERROR_IN_MATCHER");
    } else if (t == PROCESSED_WITH_ERRORS) {
      return QString("PROCESSED_WITH_ERRORS");
    } else if (t == BET_ACTION_ERROR) {
      return QString("BET_ACTION_ERROR");
    } else if (t == INVALID_ACCOUNT_STATE) {
      return QString("INVALID_ACCOUNT_STATE");
    } else if (t == INVALID_WALLET_STATUS) {
      return QString("INVALID_WALLET_STATUS");
    } else if (t == INSUFFICIENT_FUNDS) {
      return QString("INSUFFICIENT_FUNDS");
    } else if (t == LOSS_LIMIT_EXCEEDED) {
      return QString("LOSS_LIMIT_EXCEEDED");
    } else if (t == MARKET_SUSPENDED) {
      return QString("MARKET_SUSPENDED");
    } else if (t == MARKET_NOT_OPEN_FOR_BETTING) {
      return QString("MARKET_NOT_OPEN_FOR_BETTING");
    } else if (t == DUPLICATE_TRANSACTION) {
      return QString("DUPLICATE_TRANSACTION");
    } else if (t == INVALID_ORDER) {
      return QString("INVALID_ORDER");
    } else if (t == INVALID_MARKET_ID) {
      return QString("INVALID_MARKET_ID");
    } else if (t == PERMISSION_DENIED) {
      return QString("PERMISSION_DENIED");
    } else if (t == DUPLICATE_BETIDS) {
      return QString("DUPLICATE_BETIDS");
    } else if (t == NO_ACTION_REQUIRED) {
      return QString("NO_ACTION_REQUIRED");
    } else if (t == SERVICE_UNAVAILABLE) {
      return QString("SERVICE_UNAVAILABLE");
    } else if (t == REJECTED_BY_REGULATOR) {
      return QString("REJECTED_BY_REGULATOR");
    }

    return QString("UNKOWN_BfExecutionErrorReportCodeEnum");
  }
};

#endif // BFEXECUTIONREPORTERRORCODE_H

