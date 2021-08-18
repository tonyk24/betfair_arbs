#ifndef EXTBET
#define EXTBET

#include <stdexcept>

#include <QString>

class ExtBet
{
public:
  enum EnumType {
    NONE,
    MO_Home,
    MO_Draw,
    MO_Away,
    OU_Over05,
    OU_Under05,
    OU_Over15,
    OU_Under15,
    OU_Over25,
    OU_Under25 };

  ExtBet(EnumType type):
    m_name(""),
    m_type(type),
    m_odds(0.0),
    m_size(0.0),
    m_simulate(false),
    m_outCome1(0.0),
    m_outCome2(0.0),
    m_arbResult("")
  {
  }

  ExtBet(QString name, EnumType type, double odds, double size,
         bool simulate,double outCome1,double outCome2,
         QString result)
    : m_name(name),
      m_type(type),
      m_odds(odds),
      m_size(size),
      m_simulate(simulate),
      m_outCome1(outCome1),
      m_outCome2(outCome2),
      m_arbResult(result)
  {

  }


  static EnumType toEnumType(const QString &str) {
    if (str == "MO_Home") {
      return MO_Home;
    } else if (str == "MO_Draw") {
      return MO_Draw;
    } else if (str == "MO_Away") {
      return MO_Away;
    } else if (str == "OU_Over05") {
      return OU_Over05;
    } else if (str == "OU_Under05") {
      return OU_Under05;
    } else if (str == "OU_Over15") {
      return OU_Over15;
    } else if (str == "OU_Under15") {
      return OU_Under15;
    } else if (str == "OU_Over25") {
      return OU_Over25;
    } else if (str == "OU_Under25") {
      return OU_Under25;
    }
    throw std::runtime_error(QString("Expected existing enum for '%1': %2")
                             .arg(str, __PRETTY_FUNCTION__).toStdString());
  }

  static QString toTypeStr(EnumType t) {
    if (t == MO_Home) {
      return QString("MO_Home");
    } else if (t == MO_Draw) {
      return QString("MO_Draw");
    } else if (t == MO_Away) {
      return QString("MO_Away");
    } else if (t == OU_Over05) {
      return QString("OU_Over05");
    } else if (t == OU_Under05) {
      return QString("OU_Under05");
    } else if (t == OU_Over15) {
      return QString("OU_Over15");
    } else if (t == OU_Under15) {
      return QString("OU_Under15");
    } else if (t == OU_Over25) {
      return QString("OU_Over25");
    } else if (t == OU_Under25) {
      return QString("OU_Under25");
    }

    return QString("UNKOWN_EnumType");
  }

  QString m_name;
  EnumType m_type;
  double m_odds;
  double m_size;
  bool m_simulate;
  double m_outCome1;
  double m_outCome2;
  QString m_arbResult;
};

#endif // EXTBET

