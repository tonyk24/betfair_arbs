#include "eventdatalogger.h"

EventDataLogger::EventDataLogger(QObject *parent)
  : m_dataDirStr("Betfairdata"),
    m_tempDirStr("temp"),
    m_destinationDirStr("final")
{
  Q_UNUSED(parent);
}

void EventDataLogger::createDirectories() {
  QDir dataDir = QDir::home();

  if (!dataDir.exists(m_dataDirStr)) {
    dataDir.mkdir(m_dataDirStr);
  }
  dataDir.cd(m_dataDirStr);

  m_tempDir = dataDir;

  if (!m_tempDir.exists(m_tempDirStr)) {
    m_tempDir.mkdir(m_tempDirStr);
  }
  m_tempDir.cd(m_tempDirStr);

  m_destDir = dataDir;
  if (!m_destDir.exists(m_destinationDirStr)) {
    m_destDir.mkdir(m_destinationDirStr);
  }
  m_destDir.cd(m_destinationDirStr);
}

void EventDataLogger::writeEventData(const std::list<EventDataT> &eventData) {
  createDirectories();

  /*
   * Soccer Spanish Soccer Primera Division Fixtures 02 March     Osasuna v Deportivo
Half Time
Timestamp,Inplay delay,Market status,Selection ID,Selection name,RF,BP1,BV1,BP2,BV2,BP3,BV3,LP1,LV1,LP2,LV2,LP3,LV3,Total matched,LPM
   * */

  /*
   * Soccer - Spanish Soccer - Primera Division - Fixtures 01 March     - Espanyol v Mallorca - Correct Score 2.csv
   */

  QLocale engLoc(QLocale::English, QLocale::UnitedKingdom);

  for (std::list<EventDataT>::const_iterator itEventData = eventData.begin();
       itEventData != eventData.end(); itEventData++) {
    for (std::list<BetfairMarket>::const_iterator itMarket = itEventData->m_markets.begin();
         itMarket!= itEventData->m_markets.end(); itMarket++) {
      QString eventMarketId = itEventData->m_event.m_eventId + "_" + itMarket->m_marketId;

      QFile *file = 0;
      if (m_eventMarketLogFile.find(eventMarketId) == m_eventMarketLogFile.end()) {
        QString outputFileName = "Soccer-" + BfCompetition::toStr(itEventData->m_event.m_competition)
            + "-" + engLoc.toString(itEventData->m_event.m_openDate,"ddd_dd_MM_yyyy")
            + "-" + engLoc.toString(itEventData->m_event.m_openDate,"hh_mm")
            + "-" + itEventData->m_event.m_name +
            + "-" + itEventData->m_event.m_eventId +
            + "-" + itMarket->m_marketName +
            + "-" + itMarket->m_marketId + ".csv";
        outputFileName.replace("/", "");
        outputFileName.replace("?", "");
        outputFileName.replace(" ", "_");

        QString outputFilePath = m_tempDir.absolutePath() + "/" + outputFileName;
        file = new QFile(outputFilePath);
        m_eventMarketLogFile[eventMarketId] = file;

        if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
          qWarning() << "writeEventData(): Failed to write to file: " + outputFilePath;
          continue;
        }

        QTextStream outHeader(file);
        outHeader << "Timestamp,";         // 1. Timestamp
        outHeader << "Inplay delay,";      // 2. Inplay delay
        outHeader << "Market status,";     // 3. Market status
        outHeader << "Selection ID,";      // 4. Selection ID
        outHeader << "Selection name,";    // 5. Selection Name
        outHeader << "Selection status,";  // 6. Selection Status
        outHeader << "BP1,";               // 7. BP1
        outHeader << "BV1,";               // 8. BV1
        outHeader << "BP2,";               // 9. BP2
        outHeader << "BV2,";               // 10. BV2
        outHeader << "BP3,";               // 11. BP3
        outHeader << "BV3,";               // 12. BV3
        outHeader << "LP1,";               // 13. LP1
        outHeader << "LV1,";               // 14. LV1
        outHeader << "LP2,";               // 15. LP2
        outHeader << "LV2,";               // 16. LV2
        outHeader << "LP3,";               // 17. LP3
        outHeader << "LV3\n";              // 18. LV3

        outHeader.flush();
      } else {
        file = m_eventMarketLogFile[eventMarketId];
      }

      QTextStream out(file);

      for (std::list<BetfairSelection>::const_iterator itSel = itMarket->m_selections.begin();
           itSel != itMarket->m_selections.end(); itSel++) {
        // 1. Timestamp
        out << itEventData->m_dateTime.currentMSecsSinceEpoch() << ",";
        // 2. Inplay delay
        if (QDateTime::currentDateTimeUtc() > itEventData->m_event.m_openDate) {
          out << "8,";
        } else {
          out << "0,";
        }
        // 3. Market status
        out << BfMarketStatus::toStr(itMarket->m_marketStatus) << ",";
        // 4. Selection ID
        out << itSel->m_selectionId << ",";
        // 5. Selection Name
        out << itSel->m_selectionName << ",";
        // 6. Selection Status
        out << itSel->m_status << ",";
        // 7. BP1
        out << doubleToStr(itSel->m_availableToBackPrice, 0) << ",";
        // 8. BV1
        out << doubleToStr(itSel->m_availableToBackSize, 0) << ",";
        // 9. BP2
        out << doubleToStr(itSel->m_availableToBackPrice, 1) << ",";
        // 10. BV2
        out << doubleToStr(itSel->m_availableToBackSize, 1) << ",";
        // 11. BP3
        out << doubleToStr(itSel->m_availableToBackPrice, 2) << ",";
        // 12. BV3
        out << doubleToStr(itSel->m_availableToBackSize, 2) << ",";
        // 13. LP1
        out << doubleToStr(itSel->m_availableToLayPrice, 0) << ",";
        // 14. LV1
        out << doubleToStr(itSel->m_availableToLaySize, 0) << ",";
        // 15. LP2
        out << doubleToStr(itSel->m_availableToLayPrice, 1) << ",";
        // 16. LV2
        out << doubleToStr(itSel->m_availableToLaySize, 1) << ",";
        // 17. LP3
        out << doubleToStr(itSel->m_availableToLayPrice, 2) << ",";
        // 18. LV3
        out << doubleToStr(itSel->m_availableToLaySize, 2) << "\n";
      }
      out.flush();
    }
  }
}

void EventDataLogger::eventFinnished(const QString &eventId) {
  for(std::map<QString, QFile*>::iterator it = m_eventMarketLogFile.begin();
      it != m_eventMarketLogFile.end();) {
    if (it->first.contains(eventId + "_")) {
      // Close & delete file pointer
      if (it->second->isOpen()) {
        it->second->close();
        delete it->second;
      }
      // Erase element
      m_eventMarketLogFile.erase(it++);
    } else {
      it++;
    }
  }

  // Find files with event id in the name and move them from temp
  // directory to the final directory
  QStringList filter("*" + eventId + "*");
  QFileInfoList eventFilesAndDirectories = m_tempDir.entryInfoList(filter);

  for (QFileInfoList::iterator itFileInfo = eventFilesAndDirectories.begin();
       itFileInfo != eventFilesAndDirectories.end(); itFileInfo++) {
    QString newFileName = itFileInfo->absoluteFilePath().replace(m_tempDir.absolutePath(), m_destDir.absolutePath());

    QFile::rename(itFileInfo->absoluteFilePath(), newFileName);
  }
}
