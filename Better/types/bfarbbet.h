#ifndef BFARBBET_H
#define BFARBBET_H

#include <list>

#include "bftypes/bfplaceinstruction.h"
#include "bftypes/bfmarket.h"
#include "bftypes/bfselection.h"

using namespace BfLib;

class BfArbBet
{
public:
  BfArbBet(int arbBetId,
  BetfairMarket market,
  BetfairSelection selection,
  BfPlaceInstruction pi):
    m_arbBetId(arbBetId),
    m_market(market),
    m_selection(selection),
    m_pi(pi)
{}
  int m_arbBetId;
  BetfairMarket m_market;
  BetfairSelection m_selection;
  BfPlaceInstruction m_pi;
};

#endif // BFARBBET_H

