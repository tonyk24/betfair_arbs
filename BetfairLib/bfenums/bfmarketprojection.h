#ifndef BFMARKETPROJECTION_H
#define BFMARKETPROJECTION_H

#include <stdexcept>
#include <QString>

class BfMarketProjection {
public:
  enum Enum { COMPETITION,
              EVENT,
              EVENT_TYPE,
              MARKET_START_TIME,
              MARKET_DESCRIPTION,
              RUNNER_DESCRIPTION,
              RUNNER_METADATA };

  static Enum toEnum(const QString &str) {
    if (str == "COMPETITION") {
      return COMPETITION;
    } else if (str == "EVENT") {
      return EVENT;
    } else if (str == "EVENT_TYPE") {
      return EVENT_TYPE;
    } else if (str == "MARKET_START_TIME") {
      return MARKET_START_TIME;
    } else if (str == "MARKET_DESCRIPTION") {
      return MARKET_DESCRIPTION;
    } else if (str == "RUNNER_DESCRIPTION") {
      return RUNNER_DESCRIPTION;
    } else if (str == "RUNNER_METADATA") {
      return RUNNER_METADATA;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == COMPETITION) {
      return QString("COMPETITION");
    } else if (t == EVENT) {
      return QString("EVENT");
    } else if (t == EVENT_TYPE) {
      return QString("EVENT_TYPE");
    } else if (t == MARKET_START_TIME) {
      return QString("MARKET_START_TIME");
    } else if (t == MARKET_DESCRIPTION) {
      return QString("MARKET_DESCRIPTION");
    } else if (t == RUNNER_DESCRIPTION) {
      return QString("RUNNER_DESCRIPTION");
    } else if (t == RUNNER_METADATA) {
      return QString("RUNNER_METADATA");
    }

    return QString("UNKOWN_BfMarketProjectionEnum");
  }
};

#endif // BFMARKETPROJECTION_H

