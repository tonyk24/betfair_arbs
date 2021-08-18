#ifndef RESMAT_H
#define RESMAT_H

#include "bftypes/bfplaceexecutionreport.h"
#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"
#include "bftypes/bfcurrentorder.h"
#include "types/extbet.h"
#include "types/bfarbbet.h"

class ResMat
{
public:
  ResMat();
  void updateResMatPlacedBets(const BfEvent &bfEvent,
                              const std::list<BetfairMarket> &marketCatalogue,
                              std::list<std::pair<BfPlaceExecutionReport,BfCurrentOrder> > placedBets);
  void updateResMatSimulationBets(const BfEvent &bfEvent,
                                  const std::list<BetfairMarket> &marketCatalogue,
                                  std::list<BfPlaceInstruction> simulatedBets,
                                  std::list<ExtBet> extSimulatedBets);
  void updateResMatLucky(const BfEvent &bfEvent,
                         const std::list<BfArbBet> &arbBets);
  double getItemData(int row, int column);
  void reset();
private:
  double m_matrix[8][8];
};

#endif // RESMAT_H
