#ifndef BETLOGGERA_H
#define BETLOGGERA_H

#include <list>

#include <QThread>
#include <QString>
#include <QMutex>

#include "bftypes/bfplaceinstruction.h"
#include "bfenums/bfexecutionreportstatus.h"
#include "betting/activecombination.h"

using namespace BfLib;

class BetLogger : public QThread
{
  Q_OBJECT

public:

  BetLogger(QObject *parent, bool logBetsTaken);
  ~BetLogger() {}

  void placeBets(const BfEvent &event,
                 const BetfairMarket &market1,
                 ActiveComboInstruction::BetStatus betStatus1,
                 const BfPlaceInstruction &bet1,
                 const BetfairMarket &market2,
                 ActiveComboInstruction::BetStatus betStatus2,
                 const BfPlaceInstruction &bet2);
  void quit();

protected:
  void run() Q_DECL_OVERRIDE;
private:

  bool m_quit;
  bool m_logBetsTaken;

  QMutex m_loggerMutex;

  std::list<QString> m_entriesToWrite;
signals:
  void threadError(QString errormsg);
};

#endif // BETLOGGERA_H

