#ifndef BETSTATISTICS_H
#define BETSTATISTICS_H

#include <list>
#include <map>
#include <utility>

#include <QString>
#include <QObject>
#include <QDebug>

#include "betlib_global.h"

#include "bftypes/bfplaceinstruction.h"
#include "bftypes/bfplaceexecutionreport.h"
#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"

#include "betting/betlogger.h"

using namespace BfLib;

class BETLIBSHARED_EXPORT BetStatistics : public QObject {
  Q_OBJECT
public:
  BetStatistics(bool logBetsTaken);
  ~BetStatistics();

  // Input functions
  void placeBets(const BfEvent &event,
                 const BetfairMarket &market1,
                 const BetfairMarket &market2,
                 const BfPlaceInstruction &bet1,
                 const BfPlaceInstruction &bet2);
  void placeOrdersRsp(const BfPlaceExecutionReport &placeExecutionReport);

  // Output functions
  bool hasPlacedBets(QString eventId);
  bool hasActiveCombinations(QString eventId);

  bool hasUnkownActiveCombination();
  bool hasFailedActiveCombination();

  // For unit testing...
  void resetPlacedBets();

  std::list<QString> m_eventsWithPlacedBets;

  std::list<ActiveComboEvent> m_activeCombinations;
private:
  BetLogger *m_betLogger;
  bool m_logBetsTaken;
public slots:
  void threadError(QString errorno) {
    qDebug() << "Received thread error: " << errorno;
  }
};

#endif // BETSTATISTICS_H

