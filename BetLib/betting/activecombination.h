#ifndef ACTIVECOMBINATION_H
#define ACTIVECOMBINATION_H

#include <list>
#include <QString>

#include "bftypes/bfplaceinstruction.h"
#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"

using namespace BfLib;

class ActiveComboInstruction {
public:

  enum BetStatus { BET_UNKOWN, BET_TAKEN, BET_FAILED };
  ActiveComboInstruction(const BetfairMarket &market,
                         const BetStatus &status,
                         const BfPlaceInstruction &instruction)
    : m_market(market),
      m_status(status),
      m_instruction(instruction)
  {

  }

  static QString betStatusToStr(BetStatus bs) {
    if (bs == BET_UNKOWN) {
      return "BET_UNKOWN";
    } else if (bs == BET_TAKEN) {
      return "BET_TAKEN";
    } else if (bs == BET_FAILED) {
      return "BET_FAILED";
    }

    return "UNKOWN";
  }

  BetfairMarket m_market;
  BetStatus m_status;
  BfPlaceInstruction m_instruction;
};

class ActiveComboEvent {
public:
  ActiveComboEvent(const BfEvent &event,
        const std::list<ActiveComboInstruction> &combinations) :
    m_event(event),
    m_combinations(combinations) {
  }

  BfEvent m_event;
  std::list<ActiveComboInstruction> m_combinations;
};

#endif // ACTIVECOMBINATION_H

