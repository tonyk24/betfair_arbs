#ifndef DEBUGMSGLOGGER_H
#define DEBUGMSGLOGGER_H

#include <list>

#include <QThread>
#include <QString>
#include <QMutex>
#include <QFile>
#include <QTextStream>

#include "bftypes/bfplaceinstruction.h"
#include "bfenums/bfexecutionreportstatus.h"
#include "betting/activecombination.h"

class DebugMsgLogger : public QThread
{
  Q_OBJECT

public:
  DebugMsgLogger(QObject *parent);
  ~DebugMsgLogger();
  void log(QtMsgType type, const QString & msg);
  void quit();

  void clean();

protected:
  void run() Q_DECL_OVERRIDE;
private:

  void writeToFile(const std::list<std::pair<QtMsgType,QString> > &entriesToWrite);

  bool m_quit;
  QMutex m_loggerMutex;

  std::list<std::pair<QtMsgType,QString> > m_entriesToWrite;

  QFile *m_outFileInfo;
  QFile *m_outFileDebug;
  QFile *m_outFileWarning;
  QFile *m_outFileCritical;
  QFile *m_outFileFatal;
signals:
  void threadError(QString errormsg);
};


#endif // DEBUGMSGLOGGER_H

