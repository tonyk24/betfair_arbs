#ifndef BFMARKETBETTINGTYPE_H
#define BFMARKETBETTINGTYPE_H

#include <stdexcept>
#include <QString>

class BfMarketBettingType {
public:
  enum Enum {
    ODDS,
    LINE,
    RANGE,
    ASIAN_HANDICAP_DOUBLE_LINE,
    ASIAN_HANDICAP_SINGLE_LINE,
    FIXED_ODDS
  };

  static Enum toEnum(const QString &str) {
    if (str == "ODDS") {
      return ODDS;
    } else if (str == "LINE") {
      return LINE;
    } else if (str == "RANGE") {
      return RANGE;
    } else if (str == "ASIAN_HANDICAP_DOUBLE_LINE") {
      return ASIAN_HANDICAP_DOUBLE_LINE;
    } else if (str == "ASIAN_HANDICAP_SINGLE_LINE") {
      return ASIAN_HANDICAP_SINGLE_LINE;
    } else if (str == "FIXED_ODDS") {
      return FIXED_ODDS;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toStr(Enum t) {
    if (t == ODDS) {
      return QString("ODDS");
    } else if (t == LINE) {
      return QString("LINE");
    } else if (t == RANGE) {
      return QString("RANGE");
    } else if (t == ASIAN_HANDICAP_DOUBLE_LINE) {
      return QString("ASIAN_HANDICAP_DOUBLE_LINE");
    } else if (t == ASIAN_HANDICAP_SINGLE_LINE) {
      return QString("ASIAN_HANDICAP_SINGLE_LINE");
    } else if (t == FIXED_ODDS) {
      return QString("FIXED_ODDS");
    }

    return QString("UNKOWN_BfMarketBettingTypeEnum");
  }
};

#endif // BFMARKETBETTINGTYPE_H

