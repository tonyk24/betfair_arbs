
#include <list>
#include <utility>

#include <QDir>
#include <QString>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "debugmsglogger.h"

DebugMsgLogger::DebugMsgLogger(QObject *parent)
  : m_quit(false),
    m_outFileInfo(0),
    m_outFileDebug(0),
    m_outFileWarning(0),
    m_outFileCritical(0),
    m_outFileFatal(0)
{
  Q_UNUSED(parent);

  QDir dataDir = QDir::home();

  if (!dataDir.exists("Betfairdata")) {
    dataDir.mkdir("Betfairdata");
  }

  dataDir.cd("Betfairdata");

  m_outFileInfo = new QFile(dataDir.absolutePath() + "/infoLog.txt");
  m_outFileDebug = new QFile(dataDir.absolutePath() + "/debugLog.txt");
  m_outFileWarning = new QFile(dataDir.absolutePath() + "/warningLog.txt");
  m_outFileCritical = new QFile(dataDir.absolutePath() + "/criticalLog.txt");
  m_outFileFatal = new QFile(dataDir.absolutePath() + "/fatalLog.txt");

  m_outFileInfo->open(QIODevice::WriteOnly | QIODevice::Append);
  m_outFileDebug->open(QIODevice::WriteOnly | QIODevice::Append);
  m_outFileWarning->open(QIODevice::WriteOnly | QIODevice::Append);
  m_outFileCritical->open(QIODevice::WriteOnly | QIODevice::Append);
  m_outFileFatal->open(QIODevice::WriteOnly | QIODevice::Append);
}

DebugMsgLogger::~DebugMsgLogger() {
  clean();
}

void DebugMsgLogger::log(QtMsgType type, const QString & msg) {
  m_loggerMutex.lock();
  m_entriesToWrite.push_back(std::make_pair(type, msg));
  m_loggerMutex.unlock();
}

void DebugMsgLogger::quit() {
  m_quit = true;
}

void DebugMsgLogger::clean() {
  if (m_outFileInfo) {
    m_outFileInfo->close();
    delete m_outFileInfo;
    m_outFileInfo = 0;
  }
  if (m_outFileDebug) {
    m_outFileDebug->close();
    delete m_outFileDebug;
    m_outFileDebug = 0;
  }
  if (m_outFileWarning) {
    m_outFileWarning->close();
    delete m_outFileWarning;
    m_outFileWarning = 0;
  }
  if (m_outFileCritical) {
    m_outFileCritical->close();
    delete m_outFileCritical;
    m_outFileCritical = 0;
  }
  if (m_outFileFatal) {
    m_outFileFatal->close();
    delete m_outFileFatal;
    m_outFileFatal = 0;
  }
}

void DebugMsgLogger::run() {
  try {
    while (true) {
      bool nothingToDo = true;

      std::list<std::pair<QtMsgType,QString> > entriesToWrite;
      m_loggerMutex.lock();
      if (!m_entriesToWrite.empty()) {
        entriesToWrite = m_entriesToWrite;
        m_entriesToWrite.clear();
        nothingToDo = false;
      }
      m_loggerMutex.unlock();

      if (nothingToDo) {
        if (m_quit) {
          clean();
          return;
        }
        // No data in event queue, so sleep for 50 ms
        QThread::msleep(50);
      } else {
        // Write to file
        writeToFile(entriesToWrite);
        entriesToWrite.clear();
      }
    }
  } catch(...) {
    emit threadError("Caught exception in EventDataConsumer::run");
  }
}

void DebugMsgLogger::writeToFile(const std::list<std::pair<QtMsgType,QString> > &entriesToWrite) {
  QTextStream tsInfo(m_outFileInfo);
  QTextStream tsDebug(m_outFileDebug);
  QTextStream tsWarning(m_outFileWarning);
  QTextStream tsCritical(m_outFileCritical);
  QTextStream tsFatal(m_outFileFatal);

  for (std::list<std::pair<QtMsgType,QString> >::const_iterator it = entriesToWrite.begin();
       it != entriesToWrite.end(); it++) {
    switch (it->first) {
#if QT_VERSION >= 0x050500

    case QtInfoMsg:
    {
      QString txt = QString("[%1] Info: %2").arg(QDateTime::currentDateTime().toString(), it->second);
      tsInfo << txt << endl;
      break;
    }
#endif
    case QtDebugMsg:
    {
      QString txt = QString("[%1] Debug: %2").arg(QDateTime::currentDateTime().toString(), it->second);
      tsDebug << txt << endl;
      break;
    }
    case QtWarningMsg:
    {
      QString txt = QString("[%1] Warning: %2").arg(QDateTime::currentDateTime().toString(), it->second);
      tsWarning << txt << endl;
      break;
    }
    case QtCriticalMsg:
    {
      QString txt = QString("[%1] Critical: %2").arg(QDateTime::currentDateTime().toString(), it->second);
      tsCritical << txt << endl;
      break;
    }
    case QtFatalMsg:
      QString txt = QString("[%1] Fatal: %2").arg(QDateTime::currentDateTime().toString(), it->second);
      tsFatal << txt << endl;
    }
  }

  tsInfo.flush();
  if (tsInfo.status() != QTextStream::Ok) {
    m_outFileInfo->close();
    m_outFileInfo->open(QIODevice::WriteOnly | QIODevice::Append);
  }

  tsDebug.flush();
  if (tsDebug.status() != QTextStream::Ok) {
    m_outFileDebug->close();
    m_outFileDebug->open(QIODevice::WriteOnly | QIODevice::Append);
  }

  tsWarning.flush();
  if (tsWarning.status() != QTextStream::Ok) {
    m_outFileWarning->close();
    m_outFileWarning->open(QIODevice::WriteOnly | QIODevice::Append);
  }

  tsCritical.flush();
  if (tsCritical.status() != QTextStream::Ok) {
    m_outFileCritical->close();
    m_outFileCritical->open(QIODevice::WriteOnly | QIODevice::Append);
  }

  tsFatal.flush();
  if (tsFatal.status() != QTextStream::Ok) {
    m_outFileFatal->close();
    m_outFileFatal->open(QIODevice::WriteOnly | QIODevice::Append);
  }
}
