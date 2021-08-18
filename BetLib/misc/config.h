#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QTextStream>

#include "betlib_global.h"

#include "misc/bfconfig.h"

using namespace BfLib;

class BETLIBSHARED_EXPORT Config
{
public:
  Config(bool doBetTakenLogging);
  ~Config();

  void saveConfig(QString user,
                  QString passwd,
                  QString unitCounts,
                  QString unitIndex,
                  QString AppKey,
                  QString AppKeyDelayed,
                  double maxExposure,
                  bool doDataLogging,
                  bool doBetting,
                  int retrieveGroups,
                  double perRetrieveGroupFrequencyS);

  bool loadConfig();

  double getConfiguredMaxExposure();
  int getUnitCounts();
  int getUnitIndex();



  bool logData() {
    return m_doDataLogging;
  }

  bool doBetting() {
    return m_doBetting;
  }
  void setDoBetting(bool doBetting) {
    m_doBetting = doBetting;
  }

  bool logBetTakenData() {
    return m_doBetTakenLogging;
  }

  BfConfig * getBfConfig() {
    return m_bfConfig;
  }

  int getRetrieveGroups() const {
    return m_numberOfRetreivingGroups;
  }

  double getPerRetrieveGroupFrequencyS() {
    return m_perRetrieveGroupFrequencyS;
  }

  QString getDebugStr() {
    QString out;
    QTextStream tsOut(&out);

    tsOut << "* m_unitCounts= " << QString::number(m_unitCounts) << "\n";
    tsOut << "* m_unitIndex= " << QString::number(m_unitIndex) << "\n";
    tsOut << "* m_maxExposureConfigured= " << QString::number(m_maxExposureConfigured) << "\n";
    tsOut << "* m_doDataLogging= " << (m_doDataLogging?"true":"false") << "\n";
    tsOut << "* m_doBetting= " << (m_doBetting?"true":"false") << "\n";
    tsOut << "* m_doBetTakenLogging= " << (m_doBetTakenLogging?"true":"false") << "\n";
    tsOut << "* m_numberOfRetreivingGroups= " << QString::number(m_numberOfRetreivingGroups) << "\n";
    tsOut << "* m_perRetrieveGroupFrequencyS= " << QString::number(m_perRetrieveGroupFrequencyS) << "\n";

    return out;
  }

private:

  int m_unitCounts;
  int m_unitIndex;

  double m_maxExposureConfigured;

  bool m_doDataLogging;
  bool m_doBetting;
  bool m_doBetTakenLogging;
  BfConfig * m_bfConfig;

  int m_numberOfRetreivingGroups;
  double m_perRetrieveGroupFrequencyS;
};

#endif // CONFIG_H

