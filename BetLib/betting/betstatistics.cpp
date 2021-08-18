#include <utility>

#include "betting/betstatistics.h"
#include "bftypes/bflimitorder.h"
#include "bftypes/bfplaceinstruction.h"
#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"
#include "bfenums/bfexecutionreportstatus.h"
#include "bfenums/bfinstructionreportstatus.h"

#include "betting/betlogger.h"

BetStatistics::BetStatistics(bool logBetsTaken) :
  m_logBetsTaken(logBetsTaken)
{
  qDebug() << "BetStatistics()";
  m_betLogger = new BetLogger(0, logBetsTaken);
  QObject::connect(m_betLogger, SIGNAL(threadError(QString)),
                   this, SLOT(threadError(QString)));
  m_betLogger->start();
}

BetStatistics::~BetStatistics() {
  m_betLogger->quit();
  m_betLogger->wait();
  delete m_betLogger;
}

void BetStatistics::placeBets(const BfEvent &event,
                              const BetfairMarket &market1,
                              const BetfairMarket &market2,
                              const BfPlaceInstruction &bet1,
                              const BfPlaceInstruction &bet2) {


  std::list<ActiveComboInstruction> combinations;
  combinations.push_back(ActiveComboInstruction(market1, ActiveComboInstruction::BET_UNKOWN, bet1));
  combinations.push_back(ActiveComboInstruction(market2, ActiveComboInstruction::BET_UNKOWN, bet2));

  m_activeCombinations.push_back(ActiveComboEvent(event, combinations));

  m_eventsWithPlacedBets.push_back(event.m_eventId);
}

void BetStatistics::placeOrdersRsp(const BfPlaceExecutionReport &placeExecutionReport) {
  std::size_t foundPlaceBets = 0;
  // Find 2-Combinations, update status
  for (std::list<BfPlaceInstructionReport>::const_iterator itPI = placeExecutionReport.m_instructionReports.begin();
       itPI != placeExecutionReport.m_instructionReports.end(); itPI++) {
    for (std::list<ActiveComboEvent>::iterator itAC = m_activeCombinations.begin();
         itAC != m_activeCombinations.end(); itAC++) {

      for (std::list<ActiveComboInstruction>::iterator itComb1 = itAC->m_combinations.begin();
           itComb1 != itAC->m_combinations.end(); itComb1++) {
        if (itComb1->m_market.m_marketId == placeExecutionReport.m_marketId &&
            itComb1->m_instruction.m_selectionId == itPI->m_placeInstruction.m_selectionId &&
            itComb1->m_instruction.m_orderType == itPI->m_placeInstruction.m_orderType &&
            itComb1->m_instruction.m_side == itPI->m_placeInstruction.m_side &&
            itComb1->m_instruction.m_limitOrder == itPI->m_placeInstruction.m_limitOrder) {
          foundPlaceBets++;
          if (placeExecutionReport.m_status == BfExecutionReportStatus::SUCCESS) {
            itComb1->m_status = ActiveComboInstruction::BET_TAKEN;
          } else {
            itComb1->m_status = ActiveComboInstruction::BET_FAILED;
          }
        }
      }
    }
  }

  // Check that all are found
  if (foundPlaceBets != placeExecutionReport.m_instructionReports.size()) {
    qWarning() << "Expected to find " << QString::number(placeExecutionReport.m_instructionReports.size()) << " but found= " << QString::number(foundPlaceBets);
  }

  // Remove and log those with all != BET_UNKOWN
  for (std::list<ActiveComboEvent>::iterator itAC = m_activeCombinations.begin();
       itAC != m_activeCombinations.end();) {
    std::size_t counterBetsTakenOrFailed = 0;
    std::size_t counterBetsTaken = 0;
    for (std::list<ActiveComboInstruction> ::iterator itACInstr = itAC->m_combinations.begin();
         itACInstr != itAC->m_combinations.end(); itACInstr++) {
      if (itACInstr->m_status == ActiveComboInstruction::BET_TAKEN) {
        counterBetsTaken++;
      }
      if (itACInstr->m_status == ActiveComboInstruction::BET_TAKEN ||
          itACInstr->m_status == ActiveComboInstruction::BET_FAILED) {
        counterBetsTakenOrFailed++;
      }
    }

    if (counterBetsTakenOrFailed == itAC->m_combinations.size()) {
      if (counterBetsTakenOrFailed == 2) {
        std::list<ActiveComboInstruction>::iterator itACInstr1 = itAC->m_combinations.begin();
        std::list<ActiveComboInstruction>::iterator itACInstr2 = itACInstr1++;
        m_betLogger->placeBets(itAC->m_event,
                               itACInstr1->m_market,
                               itACInstr1->m_status,
                               itACInstr1->m_instruction,
                               itACInstr2->m_market,
                               itACInstr2->m_status,
                               itACInstr2->m_instruction);
      } else {
        qWarning() << "Unexpected state: BetStatistics::placeOrdersRsp";
      }
    }

    if (counterBetsTaken == itAC->m_combinations.size()) {
      itAC = m_activeCombinations.erase(itAC);
    } else {
      itAC++;
    }
  }
}

bool BetStatistics::hasPlacedBets(QString eventId) {
  for(std::list<QString>::iterator it = m_eventsWithPlacedBets.begin();
      it != m_eventsWithPlacedBets.end(); it++) {
    if (*it == eventId) {
      return true;
    }
  }

  return false;
}

bool BetStatistics::hasActiveCombinations(QString eventId) {
  for (std::list<ActiveComboEvent>::iterator itAC = m_activeCombinations.begin();
       itAC != m_activeCombinations.end(); itAC++) {
    if (itAC->m_event.m_eventId == eventId) {
      return true;
    }
  }

  return false;
}

bool BetStatistics::hasUnkownActiveCombination() {
  // TODO: Can be optimized by checking in placeOrdersRsp..
  for (std::list<ActiveComboEvent>::iterator itAC = m_activeCombinations.begin();
       itAC != m_activeCombinations.end(); itAC++) {
    for (std::list<ActiveComboInstruction>::iterator itACInstr = itAC->m_combinations.begin();
         itACInstr != itAC->m_combinations.end(); itACInstr++) {
      if (itACInstr->m_status == ActiveComboInstruction::BET_UNKOWN) {
        return true;
      }
    }
  }

  return false;
}

bool BetStatistics::hasFailedActiveCombination() {
  // TODO: Can be optimized by checking in placeOrdersRsp..
  for (std::list<ActiveComboEvent>::iterator itAC = m_activeCombinations.begin();
       itAC != m_activeCombinations.end(); itAC++) {
    for (std::list<ActiveComboInstruction>::iterator itACInstr = itAC->m_combinations.begin();
         itACInstr != itAC->m_combinations.end(); itACInstr++) {
      if (itACInstr->m_status == ActiveComboInstruction::BET_FAILED) {
        return true;
      }
    }
  }

  return false;
}

void BetStatistics::resetPlacedBets() {
  m_eventsWithPlacedBets.clear();
}

