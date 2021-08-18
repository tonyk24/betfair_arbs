#ifndef LOGSTATISTICS_H
#define LOGSTATISTICS_H

#include <QString>
#include <QDateTime>
#include <map>

#include "betlib_global.h"

#include "bftypes/bfmarket.h"

using namespace BfLib;

class BETLIBSHARED_EXPORT EventStats {
public:
  EventStats() {
  }

  // Total goals is equal to
  enum TOTALGOALS_EQ { TGEQ_UNKOWN = -1,
                    TGEQ_0 = 0,
                    TGEQ_1 = 1,
                    TGEQ_2 = 2,
                    TGEQ_3 = 3,
                    TGEQ_4 = 4,
                    TGEQ_5 = 5,
                    TGEQ_6 = 6,
                    TGEQ_7 = 7,
                    TGEQ_8 = 8,
                    TGEQ_9 = 9,
                    TGEQ_10 = 10,
                    TGEQ_11 = 11 };

  // Total goals is less or equals to
  enum TOTALGOALS_LE { TGLE_UNKOWN = -1,
                    TGLE_0,
                    TGLE_1,
                    TGLE_2,
                    TGLE_3,
                    TGLE_4,
                    TGLE_5,
                    TGLE_6,
                    TGLE_7,
                    TGLE_8,
                    TGLE_9,
                    TGLE_10,
                    TGLE_11 };

  void updateStats(QString eventId,
                   std::list<BetfairMarket> markets);

  void startGettingEvent(QString eventId);
  void stopGettingEvent(QString eventId);
  bool hasStoppedGettingEvent(QString eventId);
  bool subscribingEventMoreThan5MinutesAgo(QString eventId);

  bool marketMOOpen5MinutesAgo(QString eventId);
  bool marketMOClosedFor1Minutes(QString eventId);

  TOTALGOALS_EQ getTotalGoalsEquals(const QString &eventId);
  TOTALGOALS_LE getTotalGoalsLessEquals(const QString &eventId);

  void reportEventError(QString eventId);
  unsigned int hasEventError(QString eventId);

private:
  std::map<QString, QDateTime> m_startGettingEvent;
  std::list<QString> m_stopGettingEvent;
  std::map<QString, QDateTime> m_lastReceivedOpenMoMarketData;
  std::map<QString, QDateTime> m_firstReceivedMOMarketClosed;
  std::map<QString, unsigned int> m_eventErrors;
  std::map<QString, TOTALGOALS_EQ> m_totalGoalsEQ;
  std::map<QString, TOTALGOALS_LE> m_totalGoalsLE;
};

#endif // LOGSTATISTICS_H

