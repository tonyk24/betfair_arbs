
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

#include <QFile>
#include <QDir>

#include "config.h"
#include "misc/simplecrypt.h"

Config::Config(bool doBetTakenLogging) :
    m_unitCounts(1),
    m_unitIndex(0),
    m_maxExposureConfigured(120.0),
    m_doDataLogging(true),
    m_doBetting(false),
    m_doBetTakenLogging(doBetTakenLogging),
    m_bfConfig(0),
    m_numberOfRetreivingGroups(5),
    m_perRetrieveGroupFrequencyS(0.2)
{
  if(!loadConfig())
  {
    qDebug() << "loadConfig failed";
  }

  saveConfig(m_bfConfig->getUsername(),
             m_bfConfig->getPassword(),
             QString::number(m_unitCounts),
             QString::number(m_unitIndex),
             m_bfConfig->getAppKeyNonDelayed(),
             m_bfConfig->getAppKeyDelayed(),
             m_maxExposureConfigured,
             m_doDataLogging,
             m_doBetting,
             m_numberOfRetreivingGroups,
             m_perRetrieveGroupFrequencyS);


  /*
  saveConfig("",   // user
             "",   // passwd
             "2",   // UnitCounts
             "0",   // UnitIndex
             "",   // AppKey
             "",   // AppKeyDelayed
            120,   // MaxExposure
            true,  // DoDataLogging
            5,     // NumberOfRetrieveGroups
            0.2    // PerRetrieveGroupFrequencyS
             );
*/
}

Config::~Config() {
  if (m_bfConfig) {
    delete m_bfConfig;
  }
}

void Config::saveConfig(QString user,
                        QString passwd,
                        QString unitCounts,
                        QString unitIndex,
                        QString AppKey,
                        QString AppKeyDelayed,
                        double maxExposure,
                        bool doDataLogging,
                        bool doBetting,
                        int retrieveGroups,
                        double perRetrieveGroupFrequencyS) {


  QDir dataDir = QDir::home();

  QString dataDirStr = "Betfairdata";
  if (!dataDir.exists(dataDirStr)) {
    dataDir.mkdir(dataDirStr);
  }
  dataDir.cd(dataDirStr);

  QString outputFileName = "config_save.csv";

  QString outputFilePath = dataDir.absolutePath() + "/" + outputFileName;
  QFile file(outputFilePath);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    return;
  }

  SimpleCrypt crypto(Q_UINT64_C(0x0c2dd4a42cb9f123)); //some random number

  //Encryption
  QString result = crypto.encryptToString(passwd);

  QTextStream outHeader(&file);
  outHeader << "User,Passwd,UnitCounts,UnitIndex,AppKey,AppKeyDelayed,MaxExposure,DoDataLogging,RetrieveGroups,PerRetrieveGroupFrequencyS,DoBetting\n";
  outHeader << user << ","
            << result << ","
            << unitCounts << ","
            << unitIndex << ","
            << AppKey << ","
            << AppKeyDelayed << ","
            << QString::number(maxExposure) << ","
            << (doDataLogging?"1":"0") << ","
            << retrieveGroups << ","
            << perRetrieveGroupFrequencyS << ","
            << (doBetting?"1":"0")
            << "\n";

  file.close();
}

bool Config::loadConfig() {
  QDir dataDir = QDir::home();



  QString dataDirStr = "Betfairdata";
  if (!dataDir.exists(dataDirStr)) {
    // Do something
    qDebug() << "Datadir does not exists";
  }
  dataDir.cd(dataDirStr);

  QString outputFileName = "config.csv";
  QString outputFilePath = dataDir.absolutePath() + "/" + outputFileName;

  QFile inputFile(outputFilePath);
  if (inputFile.open(QIODevice::ReadOnly))
  {
    QString bfuser;
    QString bfPasswd;

    QString appKey;
    QString appKeyDelayed;

    QTextStream in(&inputFile);
    QString line = in.readLine(); // Read header
    line = in.readLine();
    QStringList strList = line.split(",");
    if (strList.size() > 0) {
      bfuser = strList.at(0);
    }
    if (strList.size() > 1) {
      SimpleCrypt crypto(Q_UINT64_C(0x0c2dd4a42cb9f123)); //some random number
      //Decryption
      QString decrypted = crypto.decryptToString(strList.at(1));
      bfPasswd = decrypted;
      //qDebug() << bfPasswd;
    }
    if (strList.size() > 2) {
      bool ok = false;
      m_unitCounts = strList.at(2).toInt(&ok);
      if (!ok) {
        m_unitCounts = 1;
      }
    }
    if (strList.size() > 3) {
      bool ok = false;
      m_unitIndex = strList.at(3).toInt(&ok);
      if (!ok) {
        m_unitIndex = 0;
      }
    }
    if (strList.size() > 4) {
      appKey = strList.at(4);
    }
    if (strList.size() > 5) {
      appKeyDelayed = strList.at(5);
    }
    if (strList.size() > 6) {
      bool ok = false;
      m_maxExposureConfigured = strList.at(6).toDouble(&ok);
      if (!ok) {
        m_maxExposureConfigured = 0;
      }
    }
    if (strList.size() > 7) {
      m_doDataLogging = strList.at(7) == "1";
    }
    inputFile.close();
    if (strList.size() > 8) {
      bool ok = false;
      m_numberOfRetreivingGroups = strList.at(8).toInt(&ok);
      if (!ok) {
        m_numberOfRetreivingGroups = 5;
      }
    }
    if (strList.size() > 9) {
      bool ok = false;
      m_perRetrieveGroupFrequencyS = strList.at(9).toDouble(&ok);
      if (!ok) {
        m_perRetrieveGroupFrequencyS = 0.2;
      }
    }
    if (strList.size() > 10) {
      m_doBetting = (strList.at(10) == "1");
    }
    if (m_bfConfig != 0) {
      delete m_bfConfig;
    }
    m_bfConfig = new BfConfig(bfuser, bfPasswd, false, appKey, appKeyDelayed);


    return true;
  }

  return false;
}

double Config::getConfiguredMaxExposure() {
  return m_maxExposureConfigured;
}

int Config::getUnitCounts() {
  return m_unitCounts;
}

int Config::getUnitIndex() {
  return m_unitIndex;
}


