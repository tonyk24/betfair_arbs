#ifndef BFINSTRUCTIONREPORTERRORCODE_H
#define BFINSTRUCTIONREPORTERRORCODE_H

#include <stdexcept>
#include <QString>

class BfInstructionReportErrorCode {
public:
  enum Enum {
    NONE,
    INVALID_BET_SIZE,
    INVALID_RUNNER,
    BET_TAKEN_OR_LAPSED,
    BET_IN_PROGRESS,
    RUNNER_REMOVED,
    MARKET_NOT_OPEN_FOR_BETTING,
    LOSS_LIMIT_EXCEEDED,
    MARKET_NOT_OPEN_FOR_BSP_BETTING,
    INVALID_PRICE_EDIT,
    INVALID_ODDS,
    INSUFFICIENT_FUNDS,
    INVALID_PERSISTENCE_TYPE,
    ERROR_IN_MATCHER,
    INVALID_BACK_LAY_COMBINATION,
    ERROR_IN_ORDER,
    INVALID_BID_TYPE,
    INVALID_BET_ID,
    CANCELLED_NOT_PLACED,
    RELATED_ACTION_FAILED,
    NO_ACTION_REQUIRED
  };

  static Enum toEnum(const QString &str) {
    if (str == "INVALID_BET_SIZE") {
      return INVALID_BET_SIZE;
    } else if(str == "INVALID_RUNNER") {
      return INVALID_RUNNER;
    } else if(str == "BET_TAKEN_OR_LAPSED") {
      return BET_TAKEN_OR_LAPSED;
    } else if(str == "BET_IN_PROGRESS") {
      return BET_IN_PROGRESS;
    } else if(str == "RUNNER_REMOVED") {
      return RUNNER_REMOVED;
    } else if(str == "MARKET_NOT_OPEN_FOR_BETTING") {
      return MARKET_NOT_OPEN_FOR_BETTING;
    } else if(str == "LOSS_LIMIT_EXCEEDED") {
      return LOSS_LIMIT_EXCEEDED;
    } else if(str == "MARKET_NOT_OPEN_FOR_BSP_BETTING") {
      return MARKET_NOT_OPEN_FOR_BSP_BETTING;
    } else if(str == "INVALID_PRICE_EDIT") {
      return INVALID_PRICE_EDIT;
    } else if(str == "INVALID_ODDS") {
      return INVALID_ODDS;
    } else if(str == "INSUFFICIENT_FUNDS") {
      return INSUFFICIENT_FUNDS;
    } else if(str == "INVALID_PERSISTENCE_TYPE") {
      return INVALID_PERSISTENCE_TYPE;
    } else if(str == "ERROR_IN_MATCHER") {
      return ERROR_IN_MATCHER;
    } else if(str == "INVALID_BACK_LAY_COMBINATION") {
      return INVALID_BACK_LAY_COMBINATION;
    } else if(str == "ERROR_IN_ORDER") {
      return ERROR_IN_ORDER;
    } else if(str == "INVALID_BID_TYPE") {
      return INVALID_BID_TYPE;
    } else if(str == "INVALID_BET_ID") {
      return INVALID_BET_ID;
    } else if(str == "CANCELLED_NOT_PLACED") {
      return CANCELLED_NOT_PLACED;
    } else if(str == "RELATED_ACTION_FAILED") {
      return RELATED_ACTION_FAILED;
    } else if(str == "NO_ACTION_REQUIRED") {
      return NO_ACTION_REQUIRED;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == INVALID_BET_SIZE) {
      return QString("INVALID_BET_SIZE");
    } else if (t == INVALID_RUNNER) {
      return QString("INVALID_RUNNER");
    } else if (t == BET_TAKEN_OR_LAPSED) {
      return QString("BET_TAKEN_OR_LAPSED");
    } else if (t == BET_IN_PROGRESS) {
      return QString("BET_IN_PROGRESS");
    } else if (t == RUNNER_REMOVED) {
      return QString("RUNNER_REMOVED");
    } else if (t == MARKET_NOT_OPEN_FOR_BETTING) {
      return QString("MARKET_NOT_OPEN_FOR_BETTING");
    } else if (t == LOSS_LIMIT_EXCEEDED) {
      return QString("LOSS_LIMIT_EXCEEDED");
    } else if (t == MARKET_NOT_OPEN_FOR_BSP_BETTING) {
      return QString("MARKET_NOT_OPEN_FOR_BSP_BETTING");
    } else if (t == INVALID_PRICE_EDIT) {
      return QString("INVALID_PRICE_EDIT");
    } else if (t == INVALID_ODDS) {
      return QString("INVALID_ODDS");
    } else if (t == INSUFFICIENT_FUNDS) {
      return QString("INSUFFICIENT_FUNDS");
    } else if (t == INVALID_PERSISTENCE_TYPE) {
      return QString("INVALID_PERSISTENCE_TYPE");
    } else if (t == ERROR_IN_MATCHER) {
      return QString("ERROR_IN_MATCHER");
    } else if (t == INVALID_BACK_LAY_COMBINATION) {
      return QString("INVALID_BACK_LAY_COMBINATION");
    } else if (t == ERROR_IN_ORDER) {
      return QString("ERROR_IN_ORDER");
    } else if (t == INVALID_BID_TYPE) {
      return QString("INVALID_BID_TYPE");
    } else if (t == INVALID_BET_ID) {
      return QString("INVALID_BET_ID");
    } else if (t == CANCELLED_NOT_PLACED) {
      return QString("CANCELLED_NOT_PLACED");
    } else if (t == RELATED_ACTION_FAILED) {
      return QString("RELATED_ACTION_FAILED");
    } else if (t == NO_ACTION_REQUIRED) {
      return QString("NO_ACTION_REQUIRED");
    }

    return QString("UNKOWN_BfInstructionReportErrorCodeEnum");
  }
};

#endif // BFINSTRUCTIONREPORTERRORCODE_H

