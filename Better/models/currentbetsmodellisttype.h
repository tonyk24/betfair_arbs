#ifndef CURRENTBETSMODELLISTTYPE_H
#define CURRENTBETSMODELLISTTYPE_H

#include "bftypes/bfmarket.h"
#include "bftypes/bfselection.h"
#include "types/extbet.h"

using namespace BfLib;

class CurrentBetsModelListType
{
public:
  CurrentBetsModelListType(BetfairMarket bfMarket,
                           BetfairSelection bfSelection,
                           ExtBet extBet)
    :
      m_bfMarket(bfMarket),
      m_bfSelection(bfSelection),
      m_extBet(extBet)
  {
    m_simBfBack = false;
    m_simBfLay = false;
    m_simLaySize = 0.0;
  }

public:
  BetfairMarket m_bfMarket;
  BetfairSelection m_bfSelection;
  ExtBet m_extBet;
  bool m_simBfBack;
  bool m_simBfLay;
  double m_simLaySize;
};

#endif // CURRENTBETSMODELLISTTYPE_H

