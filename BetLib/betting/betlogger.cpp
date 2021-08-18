#include <list>

#include <QDir>
#include <QString>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "betlogger.h"

#include "bftypes/bfevent.h"
#include "bftypes/bfplaceinstruction.h"
#include "bfenums/bfexecutionreportstatus.h"
#include "betting/betstatistics.h"

BetLogger::BetLogger(QObject *parent, bool logBetsTaken)
  : m_quit(false),
    m_logBetsTaken(logBetsTaken)
{
  qDebug() << "BetLogger()";
  Q_UNUSED(parent);
}

void BetLogger::placeBets(const BfEvent &event,
                          const BetfairMarket &market1,
                          ActiveComboInstruction::BetStatus betStatus1,
                          const BfPlaceInstruction &bet1,
                          const BetfairMarket &market2,
                          ActiveComboInstruction::BetStatus betStatus2,
                          const BfPlaceInstruction &bet2) {
  m_loggerMutex.lock();
  QString s;
  QTextStream out(&s);

  // 1.  Timestamp
  out << QDateTime::currentDateTimeUtc().toMSecsSinceEpoch() << ",";
  // 2.  DateTime
  out << QDateTime::currentDateTimeUtc().toString() << ",";
  // 3.  EventStart
  out << event.m_openDate.toMSecsSinceEpoch() << ",";
  // 4.  EventId
  out << event.m_eventId << ",";
  // 5.  EventName
  out << event.m_name << ",";
  // 6.  Competition
  out << BfCompetition::toStr(market1.m_competition) << ",";
  // 7.  MarketId1
  out << market1.m_marketId << ",";
  // 8.  MarketName1
  out << market1.m_marketName << ",";
  // 9.  SelectionId1
  out << bet1.m_selectionId << ",";
  // 10.  SelectionName1
  out << market1.getSelName(bet1.m_selectionId) << ",";
  // 11  TakePrice1
  out << QString::number(bet1.m_limitOrder.m_price) << ",";
  // 12. TakeSize1
  out << QString::number(bet1.m_limitOrder.m_size) << ",";
  // 13. Side1
  out << BfSide::toStr(bet1.m_side) << ",";
  // 14. Status1
  out << ActiveComboInstruction::betStatusToStr(betStatus1) << ",";
  // 15. MarketId2
  out << market2.m_marketId << ",";
  // 16. MarketName2
  out << market2.m_marketName << ",";
  // 17. SelectionId2
  out << bet2.m_selectionId << ",";
  // 18. SelectionName2
  out << market2.getSelName(bet2.m_selectionId) << ",";
  // 19. TakePrice2
  out << QString::number(bet2.m_limitOrder.m_price) << ",";
  // 20. TakeSize2
  out << QString::number(bet2.m_limitOrder.m_size) << ",";
  // 21. Side2
  out << BfSide::toStr(bet2.m_side) << ",";
  // 22. Status2
  out << ActiveComboInstruction::betStatusToStr(betStatus2);

  m_entriesToWrite.push_back(s);
  qDebug() << "m_entriesToWrite.size()=" << QString::number(m_entriesToWrite.size());
  m_loggerMutex.unlock();
}

void BetLogger::quit() {
  m_quit = true;
}

void BetLogger::run() {
  try {
    while (true) {
      bool nothingToDo = true;

      std::list<QString> entriesToWrite;
      m_loggerMutex.lock();
      if (!m_entriesToWrite.empty()) {
        entriesToWrite = m_entriesToWrite;
        m_entriesToWrite.clear();
        nothingToDo = false;
      }
      m_loggerMutex.unlock();

      if (nothingToDo || !m_logBetsTaken) {
        if (m_quit) {
          return;
        }
        // No data in event queue, so sleep for 50 ms
        QThread::msleep(50);
      } else {
        // Create directory
        QDir dataDir = QDir::home();

        if (!dataDir.exists("Betfairdata")) {
          dataDir.mkdir("Betfairdata");
        }

        dataDir.cd("Betfairdata");
        // Write file data
        QString outputFilePath = dataDir.absolutePath() + "/betlogging.csv";
        QFile file(outputFilePath);

        if (!file.exists()) {
          if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "writeEventData(): Failed to write to file: " + outputFilePath;
            throw std::bad_exception();
            return;
          }
          QTextStream outHeader(&file);
          outHeader << "Timestamp,";      // 1.  Timestamp
          outHeader << "DateTime,";       // 2.  DateTime
          outHeader << "EventStart,";     // 3.  EventStart
          outHeader << "EventId,";        // 4.  EventId
          outHeader << "EventName,";      // 5.  EventName
          outHeader << "Competition,";    // 6.  Competition
          outHeader << "MarketId1,";      // 7.  MarketId1
          outHeader << "MarketName1,";    // 8.  MarketName1
          outHeader << "SelectionId1,";   // 9.  SelectionId1
          outHeader << "SelectionName1,"; // 10  SelectionName1
          outHeader << "TakePrice1,";     // 11  TakePrice1
          outHeader << "TakeSize1,";      // 12. TakeSize1
          outHeader << "Side1,";          // 13. Side1
          outHeader << "Status1,";        // 14. Status1
          outHeader << "MarketId2,";      // 15. MarketId2
          outHeader << "MarketName2,";    // 16. MarketName2
          outHeader << "SelectionId2,";   // 17. SelectionId2
          outHeader << "SelectionName2,"; // 18. SelectionName2
          outHeader << "TakePrice2,";     // 19. TakePrice2
          outHeader << "TakeSize2,";      // 20. TakeSize2
          outHeader << "Side2,";          // 21. Side2
          outHeader << "Status2" << "\n"; // 22. Status2

          outHeader.flush();
        }

        if (!file.isOpen()) {
          if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qWarning() << "Failed to write to file: " + outputFilePath;
            throw std::bad_exception();
            return;
          }
        }

        QTextStream outContent(&file);

        for (std::list<QString>::iterator it = entriesToWrite.begin();
             it != entriesToWrite.end(); it++) {
          outContent << *it << "\n";
        }

        outContent.flush();

        file.close();
      }
    }
  } catch(...) {
    emit threadError("Caught exception in EventDataConsumer::run");
  }
}
