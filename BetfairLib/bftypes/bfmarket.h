#ifndef BETFAIRMARKET
#define BETFAIRMARKET

#include <QString>

#include "bftypes/bfselection.h"
#include "bfenums/bfcompetition.h"
#include "bfenums/bfmarketstatus.h"

class BetfairMarket
{
public:
  BetfairMarket(QString marketId, QString marketName, double totalMatched) :
    m_marketId(marketId),
    m_marketName(marketName),
    m_marketStatus(BfMarketStatus::INACTIVE),
    m_totalMatched(totalMatched),
    m_competition(BfCompetition::UNKOWN) {
  }
  BetfairMarket(QString marketId, double totalMatched) :
    m_marketId(marketId),
    m_marketName(""),
    m_marketStatus(BfMarketStatus::INACTIVE),
    m_totalMatched(totalMatched),
    m_competition(BfCompetition::UNKOWN) {
  }

  bool hasSelectionData() {
    return m_selections.size() > 0;
  }

  QString getSelName(const qint64 &selId) const {
    for (std::list<BetfairSelection>::const_iterator it =  m_selections.begin();
         it != m_selections.end(); it++) {
      if (it->m_selectionId == selId) {
        return it->m_selectionName;
      }
    }
    return "unkown";
  }

  QString m_marketId;
  QString m_marketName;
  BfMarketStatus::Enum m_marketStatus;
  double m_totalMatched;

  BfCompetition::Competition m_competition;

  std::list<BetfairSelection> m_selections;
};

#endif // BETFAIRMARKET

