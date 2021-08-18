#include <list>
#include <map>
#include <cmath>
#include <utility>
#include <sstream>

#include <QDebug>

#include "betting/bethandler.h"
#include "betting/betstatistics.h"
#include "betting/betlogger.h"

#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"
#include "bftypes/bfselection.h"
#include "bftypes/bflimitorder.h"
#include "bftypes/bfplaceinstruction.h"
#include "bfenums/bfexecutionreportstatus.h"
#include "bfenums/bfinstructionreportstatus.h"

#define VER_DEBUG1 0
#define VER_DEBUG2 1

#include "misc/debugmacros.h"

BetHandler::BetHandler(QObject *parent,
                       AccountsHandler *accountsHandler,
                       EventStats *eventStats,
                       Config *config) :
  m_betStats(config->logBetTakenData()),
  m_accountsHandler(accountsHandler),
  m_eventStats(eventStats),
  m_config(config) {
  qDebug() << "BetHandler()";
  Q_UNUSED(parent);

  qDebug() << "Initialize BetHandler::BetHandler(maxExposure= "
           << accountsHandler->getConfiguredMaxExposure();
}

BetHandler::~BetHandler() {
  m_accountsHandler = 0;
}

void BetHandler::placeOrdersRsp(const BfPlaceExecutionReport &placeExecutionReport) {
  DEBUG2("placeOrdersRsp: " << placeExecutionReport.toStr());
  m_betStats.placeOrdersRsp(placeExecutionReport);

  if (!m_betStats.hasUnkownActiveCombination()) {
    m_accountsHandler->noPlaceBetsActive();
  }
}

void BetHandler::chooseBets(const BfEvent &event,
                            const std::list<BetfairMarket> &markets,
                            std::map<QString, std::list<BfPlaceInstruction> > &placeBets) {
  std::list<TwoCombination> twoCombinations;
  findTwoCombinations(event, markets, twoCombinations);

  //DEBUG2("BetHandler::chooseBets()= FOund combinations " << twoCombinations.size());

  for (std::list<TwoCombination>::iterator it = twoCombinations.begin();
       it != twoCombinations.end(); it++) {
    if ( it->m_type == TwoCombination::BACKNG_NO_GOAL_to_BACKOU05_OVER ||
        it->m_type == TwoCombination::BACKCS_0_0_to_BACKOU05_OVER ||
        it->m_type == TwoCombination::BACKOU05_UNDER_to_BACKTG_1_OR_MORE ||
        it->m_type == TwoCombination::BACKOU15_UNDER_to_BACKTG_2_OR_MORE ||
        it->m_type == TwoCombination::BACKOU25_UNDER_to_BACKTG_3_OR_MORE ||
        it->m_type == TwoCombination::BACKOU35_UNDER_to_BACKTG_4_OR_MORE ||
        it->m_type == TwoCombination::BACKOU45_UNDER_to_BACKTG_5_OR_MORE) {
      std::pair<double, double> backFirst = it->selection1->getBack();
      std::pair<double, double> backSecond = it->selection2->getBack();
      if (hasData(backFirst, backSecond)) {
        double p1 = 1.0/backFirst.first;
        double p2 = 1.0/backSecond.first;

        if (p1+p2 < 0.97) {
          DEBUG2("Found arbitrage bet back/back " << event.m_eventId << " {" << it->market1->m_marketName << "," << it->selection1->m_selectionName
                 << "} {" << it->market2->m_marketName << "," << it->selection2->m_selectionName << "}"
                 << "(price= " << backFirst.first << ", size= " << backFirst.second << ") ("
                 << "(price= " << backSecond.first << ", size= " << backSecond.second << ") (");

          // Example take
          double p1_norm = p1/(p1+p2);
          double p2_norm = p2/(p1+p2);

          double impliedMaxExposure1 = backFirst.second / p1_norm;
          double impliedMaxExposure2 = backSecond.second / p2_norm;

          double localMaxExposure = std::min(std::min(impliedMaxExposure1, impliedMaxExposure2),
                                             m_accountsHandler->getMaxExposure());

          DEBUG2("impliedMaxExposure1= " << impliedMaxExposure1);
          DEBUG2("impliedMaxExposure2= " << impliedMaxExposure2);

          // Get maxPlacement from maxExposure
          // size1 + *size2              < maxExposure =>
          // size*p1_norm + size*p2_norm < maxExposure =>
          // size < maxExposure

          double takePrice1 = backFirst.first;
          double takeSize1 = localMaxExposure * p1_norm;
          if (impliedMaxExposure1 == localMaxExposure) {
            takeSize1 = backFirst.second;
          }
          else {
            takeSize1 = floor( takeSize1 * 10.0 ) / 10.0;
          }

          double takePrice2 = backSecond.first;
          double takeSize2 = localMaxExposure * p2_norm;
          if (impliedMaxExposure2 == localMaxExposure) {
            takeSize2 = backSecond.second;
          } else {
            takeSize2 = floor( takeSize2 * 10.0 ) / 10.0;
          }

          DEBUG2("(takePrice1=" << QString::number(takePrice1) << ", takeSize1= " << QString::number(takeSize1) << ", takePrice2= " << QString::number(takePrice2) << ",takeSize2=" << QString::number(takeSize2));
          DEBUG2("Outcome1: " << QString::number((takePrice1-1)*takeSize1 - takeSize2));
          DEBUG2("Outcome2: " << QString::number(-takeSize1 + (takePrice2-1)*takeSize2));

          if (takeSize1 >= std::min(30.0, backFirst.second) &&
              takeSize2 >= std::min(30.0, backSecond.second) &&
              takeSize1 <= backFirst.second &&
              takeSize2 <= backSecond.second) {

            BfPlaceInstruction bet1(BfOrderType::LIMIT,
                                    it->selection1->m_selectionId,
                                    it->selection1->m_handicap,
                                    BfSide::BACK,
                                    BfLimitOrder(takePrice1, takeSize1, BfPersistenceType::LAPSE));
            BfPlaceInstruction bet2(BfOrderType::LIMIT,
                                    it->selection2->m_selectionId,
                                    it->selection2->m_handicap,
                                    BfSide::BACK,
                                    BfLimitOrder(takePrice2, takeSize2, BfPersistenceType::LAPSE));


            doPlaceBets(event,
                        *(it->market1),
                        bet1,
                        *(it->market2),
                        bet2,
                        placeBets);

          }
          else {
            // TODO: Try to find arb bet with no loss on any outcome...
            DEBUG2("Bet not within limits");
            /*
             * takeSize2 > takeSize1
             * takeSize2 < takeSize1 * (takePrice1 -1) / (takePrice2-1)
             * takeSize1 > min(avail1,30.0)
             * takeSize2 > min(avail2,30.0)
             * takeSize1 < avail1
             * takeSize2 < avail2
             * */

            /*
            double maxTakeSize1 = -1.0, maxTakeSize2 = -1.0, maxOutCome2 = -1.0, resolution = 100.0;

            double min_s1 = std::min(backFirst.second, 30.0);
            double max_s1 = backFirst.second;
            double step1 = (max_s1-min_s1) / resolution;

            double ratio = (takePrice1-1.0) / (takePrice2-1);

            for (double is1 = 0; is1 < resolution; is1 += 1.0) {
              double s1 = min_s1 + step1*is1;

              double min_s2 = std::max(s1, std::min(backSecond.second, 30.0));
              double max_s2 = std::min(s1 * ratio, backSecond.second);
              double step2 = (max_s2-min_s2) / resolution;
              for (int is2 = 0; is2 < 100; is2++) {
                double s2 = min_s2 + step2*is2;
                // Maximize outcome2

              }
            }

            if (maxTakeSize1 > 0.0 && maxTakeSize2 > 0.0 && maxOutCome2 > 0.0) {
              DEBUG2("Outcome1: " << QString::number((takePrice1-1)*maxTakeSize1 - maxTakeSize2));
              DEBUG2("Outcome2: " << QString::number(-maxTakeSize1 + (takePrice2-1)*maxTakeSize2));
            }
            */
          }
        }
      }
    } else if ( it->m_type == TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER ||
               it->m_type == TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER ||
               it->m_type == TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE ||
               it->m_type == TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE ||
               it->m_type == TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE ||
               it->m_type == TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE ||
               it->m_type == TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE ||
               it->m_type == TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL ||
               it->m_type == TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0 ||
               it->m_type == TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER ||
               it->m_type == TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER ||
               it->m_type == TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER ||
               it->m_type == TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER ||
               it->m_type == TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER ||
               it->m_type == TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0 ||
               it->m_type == TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL
               ) {
      std::pair<double, double> backFirst = it->selection1->getBack();
      std::pair<double, double> laySecond = it->selection2->getLay();
      if (hasData(backFirst, laySecond)) {
        double p1 = 1.0/backFirst.first;
        double p2_lay = 1.0 - (1.0/laySecond.first);

        if (p1+p2_lay < 0.97) {

          DEBUG2("Found arbitrage bet back/lay " << event.m_eventId << "{" << it->market1->m_marketName << "," << it->selection1->m_selectionName
                 << "} {" << it->market2->m_marketName << "," << it->selection2->m_selectionName << "}"
                 << "(price= " << backFirst.first << ", size= " << backFirst.second << ") ("
                 << "(price= " << laySecond.first << ", size= " << laySecond.second << ") (");
          double p1_norm = p1/(p1+p2_lay);
          double p2_norm = p2_lay/(p1+p2_lay);

          DEBUG2("p1_norm= " << p1_norm);
          DEBUG2("p2_norm= " << p2_norm);

          double impliedMaxExposure1 = backFirst.second / p1_norm;
          double impliedMaxExposure2 = (laySecond.first-1.0) * laySecond.second / p2_norm;

          DEBUG2("impliedMaxExposure1= " << impliedMaxExposure1);
          DEBUG2("impliedMaxExposure2= " << impliedMaxExposure2);

          double localMaxExposure = std::min(std::min(impliedMaxExposure1, impliedMaxExposure2),
                                             m_accountsHandler->getMaxExposure());

          double takePrice1 = backFirst.first;
          double takeSize1 = localMaxExposure * p1_norm;
          if (impliedMaxExposure1 == localMaxExposure) {
            takeSize1 = backFirst.second;
          }
          else {
            takeSize1 = floor( takeSize1 * 10.0 ) / 10.0;
          }

          double takePrice2 = laySecond.first;
          double takeSize2 = 0.0;
          if (impliedMaxExposure2 == localMaxExposure) {
            takeSize2 = laySecond.second;
          } else {
            double maxExposure2 = localMaxExposure * p2_norm;
            takeSize2 = maxExposure2 / (takePrice2-1.0);
            takeSize2 = round( takeSize2 * 10.0 ) / 10.0;
          }

          DEBUG2("(takePrice1=" << QString::number(takePrice1) << ", takeSize1= " << QString::number(takeSize1) << ", takePrice2= " << QString::number(takePrice2) << ",takeSize2=" << QString::number(takeSize2));
          DEBUG2("Outcome1: " << QString::number((takePrice1-1.0)*takeSize1 - (takePrice2-1.0)*takeSize2));
          DEBUG2("Outcome2: " << QString::number(-takeSize1+takeSize2));

          if (takeSize1 >= std::min(30.0, backFirst.second) &&
              takeSize2 >= std::min(30.0, laySecond.second) &&
              takeSize1 <= backFirst.second &&
              takeSize2 <= laySecond.second) {

            BfPlaceInstruction bet1 = BfPlaceInstruction(BfOrderType::LIMIT,
                                                        it->selection1->m_selectionId,
                                                         it->selection1->m_handicap,
                                                        BfSide::BACK,
                                                        BfLimitOrder(takePrice1, takeSize1, BfPersistenceType::LAPSE));

            BfPlaceInstruction bet2 = BfPlaceInstruction(BfOrderType::LIMIT,
                                                         it->selection2->m_selectionId,
                                                         it->selection2->m_handicap,
                                                         BfSide::LAY,
                                                         BfLimitOrder(takePrice2, takeSize2, BfPersistenceType::LAPSE));

            doPlaceBets(event,
                        *(it->market1),
                        bet1,
                        *(it->market2),
                        bet2,
                        placeBets);

          }
          else  {
            // TODO: Try to find arb bet with no loss on any outcome...
            DEBUG2("Bet not within limits");

            if (takeSize1 < std::min(30.0, backFirst.second) &&
                takeSize2 < std::min(30.0, laySecond.second)) {
              DEBUG2("Bet not within limits");
            } else if (takeSize2 < std::min(30.0, laySecond.second)) {
              DEBUG2("Bet not within limits, In the future");
            } else if (takeSize1 < std::min(30.0, backFirst.second)) {
              takeSize1 = std::min(30.0, backFirst.second);

              double maxExposure2 = localMaxExposure - takeSize1;
              takeSize2 = maxExposure2 / (takePrice2-1.0);
              takeSize2 = round( takeSize2 * 10.0 ) / 10.0;

              DEBUG2("(takePrice1=" << QString::number(takePrice1) << ", takeSize1= " << QString::number(takeSize1) << ", takePrice2= " << QString::number(takePrice2) << ",takeSize2=" << QString::number(takeSize2));
              double outcome1 = (takePrice1-1.0)*takeSize1 - (takePrice2-1.0)*takeSize2;
              double outcome2 =-takeSize1+takeSize2;
              DEBUG2("Outcome1: " << QString::number(outcome1));
              DEBUG2("Outcome2: " << QString::number(outcome2));

              if (takeSize1 >= std::min(30.0, backFirst.second) &&
                  takeSize2 >= std::min(30.0, laySecond.second) &&
                  takeSize1 <= backFirst.second &&
                  takeSize2 <= laySecond.second &&
                  outcome1 >= 0.0 &&
                  outcome2 >= 0.0) {

                BfPlaceInstruction bet1 = BfPlaceInstruction(BfOrderType::LIMIT,
                                                            it->selection1->m_selectionId,
                                                             it->selection1->m_handicap,
                                                            BfSide::BACK,
                                                            BfLimitOrder(takePrice1, takeSize1, BfPersistenceType::LAPSE));

                BfPlaceInstruction bet2 = BfPlaceInstruction(BfOrderType::LIMIT,
                                                             it->selection2->m_selectionId,
                                                             it->selection2->m_handicap,
                                                             BfSide::LAY,
                                                             BfLimitOrder(takePrice2, takeSize2, BfPersistenceType::LAPSE));

                doPlaceBets(event,
                            *(it->market1),
                            bet1,
                            *(it->market2),
                            bet2,
                            placeBets);

              } else {
                DEBUG2("Bet not within limits");
              }
            }
          }
        }
      }
    } else if ( it->m_type == TwoCombination::LAYNG_NO_GOAL_to_LAYOU05_OVER ||
               it->m_type == TwoCombination::LAYCS_0_0_to_LAYOU05_OVER ||
               it->m_type == TwoCombination::LAYO05_UNDER_to_LAY_TG_1_OR_MORE ||
               it->m_type == TwoCombination::LAYO15_UNDER_to_LAY_TG_2_OR_MORE ||
               it->m_type == TwoCombination::LAYO25_UNDER_to_LAY_TG_3_OR_MORE ||
               it->m_type == TwoCombination::LAYO35_UNDER_to_LAY_TG_4_OR_MORE ||
               it->m_type == TwoCombination::LAYO45_UNDER_to_LAY_TG_5_OR_MORE) {
      std::pair<double, double> layFirst = it->selection1->getLay();
      std::pair<double, double> laySecond = it->selection2->getLay();
      if (hasData(layFirst, laySecond)) {
        double p1_lay = 1.0 - (1.0/layFirst.first);
        double p2_lay = 1.0 - (1.0/laySecond.first);

        if (p1_lay+p2_lay < 0.97) {
          DEBUG2("Found arbitrage bet lay/lay " << event.m_eventId << " {" << it->market1->m_marketName << "," << it->selection1->m_selectionName
                 << "} {" << it->market2->m_marketName << "," << it->selection2->m_selectionName << "}"
                 << "(price= " << layFirst.first << ", size= " << layFirst.second << ") ("
                 << "(price= " << laySecond.first << ", size= " << laySecond.second << ") (");
          double p1_norm = p1_lay/(p1_lay+p2_lay);
          double p2_norm = p2_lay/(p1_lay+p2_lay);

          double impliedMaxExposure1 = (layFirst.first-1.0) * layFirst.second / p1_norm;
          double impliedMaxExposure2 = (laySecond.first-1.0) * laySecond.second / p2_norm;

          DEBUG2("impliedMaxExposure1= " << impliedMaxExposure1);
          DEBUG2("impliedMaxExposure2= " << impliedMaxExposure2);

          double localMaxExposure = std::min(std::min(impliedMaxExposure1, impliedMaxExposure2),
                                             m_accountsHandler->getMaxExposure());

          double takePrice1 = layFirst.first;

          double takeSize1 = 0.0;
          if (impliedMaxExposure1 == localMaxExposure) {
            takeSize1 = layFirst.second;
          } else {
            double maxExposure1 = localMaxExposure * p1_norm;
            takeSize1 = maxExposure1 / (takePrice1-1.0);
            takeSize1 = round( takeSize1 * 10.0 ) / 10.0;
          }

          double takePrice2 = laySecond.first;
          double takeSize2 = 0.0;
          if (impliedMaxExposure2 == localMaxExposure) {
            takeSize2 = laySecond.second;
          } else {
            double maxExposure2 = localMaxExposure * p2_norm;
            takeSize2 = maxExposure2 / (takePrice2-1.0);
            takeSize2 = round( takeSize2 * 10.0 ) / 10.0;
          }

          DEBUG2("(takePrice1=" << QString::number(takePrice1) << ", takeSize1= " << QString::number(takeSize1) << ", takePrice2= " << QString::number(takePrice2) << ",takeSize2=" << QString::number(takeSize2));
          DEBUG2("Outcome1: " << QString::number(takeSize1 - (takePrice2-1.0)*takeSize2));
          DEBUG2("Outcome2: " << QString::number(takeSize2 - (takePrice1-1.0)*takeSize1));

          if (takeSize1 >= std::min(30.0, layFirst.second) &&
              takeSize2 >= std::min(30.0, laySecond.second) &&
              takeSize1 <= layFirst.second &&
              takeSize2 <= laySecond.second) {

            BfPlaceInstruction bet1 = BfPlaceInstruction(BfOrderType::LIMIT,
                                                         it->selection1->m_selectionId,
                                                         it->selection1->m_handicap,
                                                         BfSide::LAY,
                                                         BfLimitOrder(takePrice1, takeSize1, BfPersistenceType::LAPSE));
            BfPlaceInstruction bet2 = BfPlaceInstruction(BfOrderType::LIMIT,
                                                         it->selection2->m_selectionId,
                                                         it->selection2->m_handicap,
                                                         BfSide::LAY,
                                                         BfLimitOrder(takePrice2, takeSize2, BfPersistenceType::LAPSE));
            doPlaceBets(event,
                        *(it->market1),
                        bet1,
                        *(it->market2),
                        bet2,
                        placeBets);
          }
        }
      }
    } else {
      DEBUG2(QString("Unkown betting type combination: %1").arg(QString::number(it->m_type)));
    }
  }
}

void BetHandler::doPlaceBets(const BfEvent &event,
                             const BetfairMarket &market1,
                             const BfPlaceInstruction &bet1,
                             const BetfairMarket &market2,
                             const BfPlaceInstruction &bet2,
                             std::map<QString, std::list<BfPlaceInstruction> > &placeBets) {

  if (!m_config->doBetting()) {
    DEBUG2("Betting disabled, not taking bets..");
    return;
  }

  if (!m_accountsHandler->isInfoUpToDate()) {
    qDebug() << "BetHandler::doPlaceBets" << " Not checking bets since account info no up to date.";
    return;
  }

  if (m_betStats.hasFailedActiveCombination()) {
    qDebug() << "BetHandler::doPlaceBets: Don't take bets while there is a failed active combinatio... should restart...";
    return;
  }

  // Check max exposure limit
  double exposure = 0.0;
  if (bet1.m_side == BfSide::BACK) {
    exposure += bet1.m_limitOrder.m_size;
  } else {
    exposure += (bet1.m_limitOrder.m_price-1.0)*bet1.m_limitOrder.m_size;
  }
  if (bet2.m_side == BfSide::BACK) {
    exposure += bet2.m_limitOrder.m_size;
  } else {
    exposure += (bet2.m_limitOrder.m_price-1.0)*bet2.m_limitOrder.m_size;
  }
  if (exposure > m_accountsHandler->getWalletFunds()) {
    qDebug() << "BetHandler::doPlaceBets: Not enouch funds, aborting...";
    return;
  }

  // Check for non-negative outcome
  if (bet1.m_side == BfSide::BACK && bet2.m_side == BfSide::BACK) {
    if (((bet1.m_limitOrder.m_price-1.0)*bet1.m_limitOrder.m_size - bet2.m_limitOrder.m_size) < 0.0 ||
        (-bet1.m_limitOrder.m_size + (bet2.m_limitOrder.m_price-1.0)*bet2.m_limitOrder.m_size) < 0.0) {
      qDebug() << "BetHandler::doPlaceBets: Expecting non-negative outcomes..";
      return;
    }
  } else if (bet1.m_side == BfSide::BACK && bet2.m_side == BfSide::LAY) {
    if (((bet1.m_limitOrder.m_price-1.0)*bet1.m_limitOrder.m_size - (bet2.m_limitOrder.m_price-1.0)*bet2.m_limitOrder.m_size) < 0.0 ||
        (-bet1.m_limitOrder.m_size+bet2.m_limitOrder.m_size) < 0.0) {
      qDebug() << "BetHandler::doPlaceBets: Expecting non-negative outcomes..";
      return;
    }
  } else if (bet1.m_side == BfSide::LAY && bet2.m_side == BfSide::LAY) {
    if ((bet1.m_limitOrder.m_size - (bet2.m_limitOrder.m_price-1.0)*bet2.m_limitOrder.m_size < 0.0) ||
        (bet2.m_limitOrder.m_size - (bet1.m_limitOrder.m_price-1.0)*bet1.m_limitOrder.m_size < 0.0)) {
      qDebug() << "BetHandler::doPlaceBets: Expecting non-negative outcomes..";
      return;
    }
  }

  DEBUG2("TGEQ= " << QString::number(m_eventStats->getTotalGoalsEquals(event.m_eventId)));
  DEBUG2("TGLE= " << QString::number(m_eventStats->getTotalGoalsLessEquals(event.m_eventId)));

  placeBets[market1.m_marketId]
      .push_back(bet1);

  placeBets[market2.m_marketId]
      .push_back(bet2);

  m_betStats.placeBets(event,
                       market1,
                       market2,
                       bet1, bet2);

  m_accountsHandler->placeBetsActive();
}

void BetHandler::findTwoCombinations(const BfEvent &event,
                                     const std::list<BetfairMarket> &markets,
                                     std::list<TwoCombination> &twoCombinations) {
  TwoCombination backNG_No_goal_to_BackOU05_Over(TwoCombination::BACKNG_NO_GOAL_to_BACKOU05_OVER);
  TwoCombination backCS_0_0_to_BackOU05_Over(TwoCombination::BACKCS_0_0_to_BACKOU05_OVER);
  TwoCombination backOU05_Under_to_backTG_1_or_more(TwoCombination::BACKOU05_UNDER_to_BACKTG_1_OR_MORE);
  TwoCombination backOU15_Under_to_BackTG_2_or_more(TwoCombination::BACKOU15_UNDER_to_BACKTG_2_OR_MORE);
  TwoCombination backOU25_Under_to_BackTG_3_or_more(TwoCombination::BACKOU25_UNDER_to_BACKTG_3_OR_MORE);
  TwoCombination backOU35_Under_to_BackTG_4_or_more(TwoCombination::BACKOU35_UNDER_to_BACKTG_4_OR_MORE);
  TwoCombination backOU45_Under_to_BackTG_5_or_more(TwoCombination::BACKOU45_UNDER_to_BACKTG_5_OR_MORE);

  TwoCombination backNG_No_goal_to_layOU05_Under(TwoCombination::BACKNG_NO_GOAL_LAYOU05_UNDER);
  TwoCombination backCS_0_0_to_layOU05_Under(TwoCombination::BACKCS_0_0_to_LAYOU05_UNDER);
  TwoCombination backOU05_Over_to_layTG_1_or_more(TwoCombination::BACKOU05_OVER_to_LAYTG_1_OR_MORE);
  TwoCombination backOU15_Over_to_layTG_2_or_more(TwoCombination::BACKOU15_OVER_to_LAYTG_2_OR_MORE);
  TwoCombination backOU25_Over_to_layTG_3_or_more(TwoCombination::BACKOU25_OVER_to_LAYTG_3_OR_MORE);
  TwoCombination backOU35_Over_to_layTG_4_or_more(TwoCombination::BACKOU35_OVER_to_LAYTG_4_OR_MORE);
  TwoCombination backOU45_Over_to_layTG_5_or_more(TwoCombination::BACKOU45_OVER_to_LAYTG_5_OR_MORE);

  TwoCombination backOU05_Under_to_layNG_No_goal(TwoCombination::BACKOU05_UNDER_to_LAYNG_NO_GOAL);
  TwoCombination backOU05_Under_to_layCS_0_0(TwoCombination::BACKOU05_UNDER_to_LAYCS_0_0);
  TwoCombination backTG_1_or_more_to_layOU05_Over(TwoCombination::BACKTG_1_OR_MORE_to_LAYOU05_OVER);
  TwoCombination backTG_2_or_more_to_layOU15_Over(TwoCombination::BACKTG_2_OR_MORE_to_LAYOU15_OVER);
  TwoCombination backTG_3_or_more_to_layOU25_Over(TwoCombination::BACKTG_3_OR_MORE_to_LAYOU25_OVER);
  TwoCombination backTG_4_or_more_to_layOU35_Over(TwoCombination::BACKTG_4_OR_MORE_to_LAYOU35_OVER);
  TwoCombination backTG_5_or_more_to_layOU45_Over(TwoCombination::BACKTG_5_OR_MORE_to_LAYOU45_OVER);

  TwoCombination backNG_No_Goal_to_layCS_0_0(TwoCombination::BACKNG_NO_GOAL_to_LAYCS_0_0);
  TwoCombination backCS_0_0_to_layNG_No_Goal(TwoCombination::BACKCS_0_0_to_LAYNG_NO_GOAL);

  TwoCombination layNG_No_goal_to_layOU05_Over(TwoCombination::LAYNG_NO_GOAL_to_LAYOU05_OVER);
  TwoCombination layCS_0_0_to_layOU05_Over(TwoCombination::LAYCS_0_0_to_LAYOU05_OVER);
  TwoCombination layOU05_Under_to_layTG_1_or_more(TwoCombination::LAYO05_UNDER_to_LAY_TG_1_OR_MORE);
  TwoCombination layOU15_Under_to_layTG_2_or_more(TwoCombination::LAYO15_UNDER_to_LAY_TG_2_OR_MORE);
  TwoCombination layOU25_Under_to_layTG_3_or_more(TwoCombination::LAYO25_UNDER_to_LAY_TG_3_OR_MORE);
  TwoCombination layOU35_Under_to_layTG_4_or_more(TwoCombination::LAYO35_UNDER_to_LAY_TG_4_OR_MORE);
  TwoCombination layOU45_Under_to_layTG_5_or_more(TwoCombination::LAYO45_UNDER_to_LAY_TG_5_OR_MORE);

  // Search
  for (std::list<BetfairMarket>::const_iterator itMarket = markets.begin();
       itMarket != markets.end(); itMarket++) {
    if (itMarket->m_marketStatus != BfMarketStatus::OPEN) {
      continue; // Skip SUSPENDED and CLOSED markets..
    }
    for (std::list<BetfairSelection>::const_iterator itSel = itMarket->m_selections.begin();
         itSel != itMarket->m_selections.end(); itSel++) {
      DEBUG1("marketName=" << itMarket->m_marketName);
      DEBUG1("selName= " << itSel->m_selectionName);

      // Back_Correct_Score_0 - 0
      if (itMarket->m_marketName == "Correct Score" &&
          itSel->m_selectionName == "0 - 0") {
        DEBUG1("Found CS_0-0");
        backCS_0_0_to_layOU05_Under.market1 = &(*itMarket);
        backCS_0_0_to_layOU05_Under.selection1 = &(*itSel);
        backCS_0_0_to_BackOU05_Over.market1 = &(*itMarket);
        backCS_0_0_to_BackOU05_Over.selection1 = &(*itSel);

        backCS_0_0_to_layNG_No_Goal.market1 = &(*itMarket);
        backCS_0_0_to_layNG_No_Goal.selection1 = &(*itSel);

        backOU05_Under_to_layCS_0_0.market2 = &(*itMarket);
        backOU05_Under_to_layCS_0_0.selection2 = &(*itSel);
        backNG_No_Goal_to_layCS_0_0.market2 = &(*itMarket);
        backNG_No_Goal_to_layCS_0_0.selection2 = &(*itSel);

        layCS_0_0_to_layOU05_Over.market1 = &(*itMarket);
        layCS_0_0_to_layOU05_Over.selection1 = &(*itSel);

      }
      // Back_Next_Goal_No Goal
      if (itMarket->m_marketName == "Next Goal" &&
          itSel->m_selectionName == "No Goal") {
        DEBUG1("Found NG_No_Goal");
        backNG_No_goal_to_BackOU05_Over.market1 = &(*itMarket);
        backNG_No_goal_to_BackOU05_Over.selection1 = &(*itSel);

        backNG_No_goal_to_layOU05_Under.market1 = &(*itMarket);
        backNG_No_goal_to_layOU05_Under.selection1 = &(*itSel);
        backNG_No_Goal_to_layCS_0_0.market1 = &(*itMarket);
        backNG_No_Goal_to_layCS_0_0.selection1 = &(*itSel);

        backOU05_Under_to_layNG_No_goal.market2 = &(*itMarket);
        backOU05_Under_to_layNG_No_goal.selection2 = &(*itSel);
        backCS_0_0_to_layNG_No_Goal.market2 = &(*itMarket);
        backCS_0_0_to_layNG_No_Goal.selection2 = &(*itSel);

        layNG_No_goal_to_layOU05_Over.market1 = &(*itMarket);
        layNG_No_goal_to_layOU05_Over.selection1 = &(*itSel);
      }
      if (itMarket->m_marketName == "Over/Under 0.5 Goals") {
        // Back_OverUnder_0.5_Goals_Over 0.5 Goals
        // Back_OverUnder_0.5_Goals_Over 0.5 Goals
        if(itSel->m_selectionName == "Over 0.5 Goals") {
          DEBUG1("Found OU05_Over");
          backNG_No_goal_to_BackOU05_Over.market2 = &(*itMarket);
          backNG_No_goal_to_BackOU05_Over.selection2 = &(*itSel);
          backCS_0_0_to_BackOU05_Over.market2 = &(*itMarket);
          backCS_0_0_to_BackOU05_Over.selection2 = &(*itSel);

          backOU05_Over_to_layTG_1_or_more.market1 = &(*itMarket);
          backOU05_Over_to_layTG_1_or_more.selection1 = &(*itSel);
          backTG_1_or_more_to_layOU05_Over.market2 = &(*itMarket);
          backTG_1_or_more_to_layOU05_Over.selection2 = &(*itSel);

          layNG_No_goal_to_layOU05_Over.market2 = &(*itMarket);
          layNG_No_goal_to_layOU05_Over.selection2 = &(*itSel);
          layCS_0_0_to_layOU05_Over.market2 = &(*itMarket);
          layCS_0_0_to_layOU05_Over.selection2 = &(*itSel);
        }
        // Back_OverUnder_0.5_Goals_Under 0.5 Goals
        if(itSel->m_selectionName == "Under 0.5 Goals") {
          DEBUG1("Found OU05_Under");
          backOU05_Under_to_backTG_1_or_more.market1 = &(*itMarket);
          backOU05_Under_to_backTG_1_or_more.selection1 = &(*itSel);
          backCS_0_0_to_layOU05_Under.market2 = &(*itMarket);
          backCS_0_0_to_layOU05_Under.selection2 = &(*itSel);

          backNG_No_goal_to_layOU05_Under.market2 = &(*itMarket);
          backNG_No_goal_to_layOU05_Under.selection2 = &(*itSel);
          backOU05_Under_to_layNG_No_goal.market1 = &(*itMarket);
          backOU05_Under_to_layNG_No_goal.selection1 = &(*itSel);
          backOU05_Under_to_layCS_0_0.market1 = &(*itMarket);
          backOU05_Under_to_layCS_0_0.selection1 = &(*itSel);

          layOU05_Under_to_layTG_1_or_more.market1 = &(*itMarket);
          layOU05_Under_to_layTG_1_or_more.selection1 = &(*itSel);
        }
      }
      // Back_OverUnder_1.5_Goals_Under 1.5 Goals
      if (itMarket->m_marketName == "Over/Under 1.5 Goals") {
        if (itSel->m_selectionName == "Under 1.5 Goals") {
          DEBUG1("Found OU15_Under");
          backOU15_Under_to_BackTG_2_or_more.market1 = &(*itMarket);
          backOU15_Under_to_BackTG_2_or_more.selection1 = &(*itSel);

          layOU15_Under_to_layTG_2_or_more.market1 = &(*itMarket);
          layOU15_Under_to_layTG_2_or_more.selection1 = &(*itSel);
        }
        if (itSel->m_selectionName == "Over 1.5 Goals") {
          DEBUG1("Found OU15_Over");
          backOU15_Over_to_layTG_2_or_more.market1 = &(*itMarket);
          backOU15_Over_to_layTG_2_or_more.selection1 = &(*itSel);
          backTG_2_or_more_to_layOU15_Over.market2 = &(*itMarket);
          backTG_2_or_more_to_layOU15_Over.selection2 = &(*itSel);
        }
      }
      // Back_OverUnder_2.5_Goals_Under 2.5 Goals
      if (itMarket->m_marketName == "Over/Under 2.5 Goals") {
        if (itSel->m_selectionName == "Under 2.5 Goals") {
          DEBUG1("Found OU25_Under");
          backOU25_Under_to_BackTG_3_or_more.market1 = &(*itMarket);
          backOU25_Under_to_BackTG_3_or_more.selection1 = &(*itSel);

          layOU25_Under_to_layTG_3_or_more.market1 = &(*itMarket);
          layOU25_Under_to_layTG_3_or_more.selection1 = &(*itSel);
        }
        if (itSel->m_selectionName == "Over 2.5 Goals") {
          DEBUG1("Found OU25_Over");
          backOU25_Over_to_layTG_3_or_more.market1 = &(*itMarket);
          backOU25_Over_to_layTG_3_or_more.selection1 = &(*itSel);
          backTG_3_or_more_to_layOU25_Over.market2 = &(*itMarket);
          backTG_3_or_more_to_layOU25_Over.selection2 = &(*itSel);
        }
      }
      // Back_OverUnder_3.5_Goals_Under 3.5 Goals
      if (itMarket->m_marketName == "Over/Under 3.5 Goals") {
        if (itSel->m_selectionName == "Under 3.5 Goals") {
          DEBUG1("Found OU35_Under");
          backOU35_Under_to_BackTG_4_or_more.market1 = &(*itMarket);
          backOU35_Under_to_BackTG_4_or_more.selection1 = &(*itSel);

          layOU35_Under_to_layTG_4_or_more.market1 = &(*itMarket);
          layOU35_Under_to_layTG_4_or_more.selection1 = &(*itSel);
        }
        if (itSel->m_selectionName == "Over 3.5 Goals") {
          DEBUG1("Found OU35_Over");
          backOU35_Over_to_layTG_4_or_more.market1 = &(*itMarket);
          backOU35_Over_to_layTG_4_or_more.selection1 = &(*itSel);
          backTG_4_or_more_to_layOU35_Over.market2 = &(*itMarket);
          backTG_4_or_more_to_layOU35_Over.selection2 = &(*itSel);
        }
      }
      // Back_OverUnder_4.5_Goals_Under 4.5 Goals
      if (itMarket->m_marketName == "Over/Under 4.5 Goals") {
        if (itSel->m_selectionName == "Under 4.5 Goals") {
          DEBUG1("Found OU45_Under");
          backOU45_Under_to_BackTG_5_or_more.market1 = &(*itMarket);
          backOU45_Under_to_BackTG_5_or_more.selection1 = &(*itSel);

          layOU45_Under_to_layTG_5_or_more.market1 = &(*itMarket);
          layOU45_Under_to_layTG_5_or_more.selection1 = &(*itSel);
        }
        if (itSel->m_selectionName == "Over 4.5 Goals") {
          DEBUG1("Found OU45_Over");
          backOU45_Over_to_layTG_5_or_more.market1 = &(*itMarket);
          backOU45_Over_to_layTG_5_or_more.selection1 = &(*itSel);
          backTG_5_or_more_to_layOU45_Over.market2 = &(*itMarket);
          backTG_5_or_more_to_layOU45_Over.selection2 = &(*itSel);
        }
      }
      // Back_Total_Goals_1 goals or more
      if (itMarket->m_marketName == "Total Goals" &&
          itSel->m_selectionName == "1 goals or more") {
        DEBUG1("Found TG_1ORMORE");
        backOU05_Under_to_backTG_1_or_more.market2 = &(*itMarket);
        backOU05_Under_to_backTG_1_or_more.selection2 = &(*itSel);

        backOU05_Over_to_layTG_1_or_more.market2 = &(*itMarket);
        backOU05_Over_to_layTG_1_or_more.selection2 = &(*itSel);
        backTG_1_or_more_to_layOU05_Over.market1 = &(*itMarket);
        backTG_1_or_more_to_layOU05_Over.selection1 = &(*itSel);

        layOU05_Under_to_layTG_1_or_more.market2 = &(*itMarket);
        layOU05_Under_to_layTG_1_or_more.selection2 = &(*itSel);
      }
      // Back_Total_Goals_2 goals or more
      if (itMarket->m_marketName == "Total Goals" &&
          itSel->m_selectionName == "2 goals or more") {
        DEBUG1("Found TG_2ORMORE");
        backOU15_Under_to_BackTG_2_or_more.market2 = &(*itMarket);
        backOU15_Under_to_BackTG_2_or_more.selection2 = &(*itSel);

        backOU15_Over_to_layTG_2_or_more.market2 = &(*itMarket);
        backOU15_Over_to_layTG_2_or_more.selection2 = &(*itSel);
        backTG_2_or_more_to_layOU15_Over.market1 = &(*itMarket);
        backTG_2_or_more_to_layOU15_Over.selection1 = &(*itSel);

        layOU15_Under_to_layTG_2_or_more.market2 = &(*itMarket);
        layOU15_Under_to_layTG_2_or_more.selection2 = &(*itSel);
      }
      // Back_Total_Goals_3 goals or more
      if (itMarket->m_marketName == "Total Goals" &&
          itSel->m_selectionName == "3 goals or more") {
        DEBUG1("Found TG_3ORMORE");
        backOU25_Under_to_BackTG_3_or_more.market2 = &(*itMarket);
        backOU25_Under_to_BackTG_3_or_more.selection2 = &(*itSel);

        backOU25_Over_to_layTG_3_or_more.market2 = &(*itMarket);
        backOU25_Over_to_layTG_3_or_more.selection2 = &(*itSel);
        backTG_3_or_more_to_layOU25_Over.market1 = &(*itMarket);
        backTG_3_or_more_to_layOU25_Over.selection1 = &(*itSel);

        layOU25_Under_to_layTG_3_or_more.market2 = &(*itMarket);
        layOU25_Under_to_layTG_3_or_more.selection2 = &(*itSel);
      }
      // Back_Total_Goals_4 goals or more
      if (itMarket->m_marketName == "Total Goals" &&
          itSel->m_selectionName == "4 goals or more") {
        DEBUG1("Found TG_4ORMORE");
        backOU35_Under_to_BackTG_4_or_more.market2 = &(*itMarket);
        backOU35_Under_to_BackTG_4_or_more.selection2 = &(*itSel);

        backOU35_Over_to_layTG_4_or_more.market2 = &(*itMarket);
        backOU35_Over_to_layTG_4_or_more.selection2 = &(*itSel);
        backTG_4_or_more_to_layOU35_Over.market1 = &(*itMarket);
        backTG_4_or_more_to_layOU35_Over.selection1 = &(*itSel);

        layOU35_Under_to_layTG_4_or_more.market2 = &(*itMarket);
        layOU35_Under_to_layTG_4_or_more.selection2 = &(*itSel);
      }
      // Back_Total_Goals_5 goals or more
      if (itMarket->m_marketName == "Total Goals" &&
          itSel->m_selectionName == "5 goals or more") {
        DEBUG1("Found TG_5ORMORE");
        backOU45_Under_to_BackTG_5_or_more.market2 = &(*itMarket);
        backOU45_Under_to_BackTG_5_or_more.selection2 = &(*itSel);

        backOU45_Over_to_layTG_5_or_more.market2 = &(*itMarket);
        backOU45_Over_to_layTG_5_or_more.selection2 = &(*itSel);
        backTG_5_or_more_to_layOU45_Over.market1 = &(*itMarket);
        backTG_5_or_more_to_layOU45_Over.selection1 = &(*itSel);

        layOU45_Under_to_layTG_5_or_more.market2 = &(*itMarket);
        layOU45_Under_to_layTG_5_or_more.selection2 = &(*itSel);
      }
    }
  }

  // Validate
  if (backNG_No_goal_to_BackOU05_Over.hasData()) {
    twoCombinations.push_back(backNG_No_goal_to_BackOU05_Over);
  }

  if (backCS_0_0_to_BackOU05_Over.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(backCS_0_0_to_BackOU05_Over);
  }

  if (backOU05_Under_to_backTG_1_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(backOU05_Under_to_backTG_1_or_more);
  }
  if (backOU15_Under_to_BackTG_2_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_2) {
    twoCombinations.push_back(backOU15_Under_to_BackTG_2_or_more);
  }
  if (backOU25_Under_to_BackTG_3_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_3) {
    twoCombinations.push_back(backOU25_Under_to_BackTG_3_or_more);
  }
  if (backOU35_Under_to_BackTG_4_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_4) {
    twoCombinations.push_back(backOU35_Under_to_BackTG_4_or_more);
  }
  if (backOU45_Under_to_BackTG_5_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_5) {
    twoCombinations.push_back(backOU45_Under_to_BackTG_5_or_more);
  }
  if (backNG_No_goal_to_layOU05_Under.hasData()) {
    twoCombinations.push_back(backNG_No_goal_to_layOU05_Under);
  }

  if (backCS_0_0_to_layOU05_Under.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(backCS_0_0_to_layOU05_Under);
  }

  if (backOU05_Over_to_layTG_1_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(backOU05_Over_to_layTG_1_or_more);
  }
  if (backOU15_Over_to_layTG_2_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_2) {
    twoCombinations.push_back(backOU15_Over_to_layTG_2_or_more);
  }
  if (backOU25_Over_to_layTG_3_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_3) {
    twoCombinations.push_back(backOU25_Over_to_layTG_3_or_more);
  }
  if (backOU35_Over_to_layTG_4_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_4) {
    twoCombinations.push_back(backOU35_Over_to_layTG_4_or_more);
  }
  if (backOU45_Over_to_layTG_5_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_5) {
    twoCombinations.push_back(backOU45_Over_to_layTG_5_or_more);
  }

  if (backOU05_Under_to_layNG_No_goal.hasData()) {
    twoCombinations.push_back(backOU05_Under_to_layNG_No_goal);
  }


  if (backOU05_Under_to_layCS_0_0.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(backOU05_Under_to_layCS_0_0);
  }

  if (backTG_1_or_more_to_layOU05_Over.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(backTG_1_or_more_to_layOU05_Over);
  }
  if (backTG_2_or_more_to_layOU15_Over.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_2) {
    twoCombinations.push_back(backTG_2_or_more_to_layOU15_Over);
  }
  if (backTG_3_or_more_to_layOU25_Over.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_3) {
    twoCombinations.push_back(backTG_3_or_more_to_layOU25_Over);
  }
  if (backTG_4_or_more_to_layOU35_Over.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_4) {
    twoCombinations.push_back(backTG_4_or_more_to_layOU35_Over);
  }
  if (backTG_5_or_more_to_layOU45_Over.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_5) {
    twoCombinations.push_back(backTG_5_or_more_to_layOU45_Over);
  }


  if (backNG_No_Goal_to_layCS_0_0.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(backNG_No_Goal_to_layCS_0_0);
  }
  if (backCS_0_0_to_layNG_No_Goal.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(backCS_0_0_to_layNG_No_Goal);
  }


  if (layNG_No_goal_to_layOU05_Over.hasData()) {
    twoCombinations.push_back(layNG_No_goal_to_layOU05_Over);
  }

  if (layCS_0_0_to_layOU05_Over.hasData() &&
    m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
    m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(layCS_0_0_to_layOU05_Over);
  }

  if (layOU05_Under_to_layTG_1_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_1) {
    twoCombinations.push_back(layOU05_Under_to_layTG_1_or_more);
  }
  if (layOU15_Under_to_layTG_2_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_2) {
    twoCombinations.push_back(layOU15_Under_to_layTG_2_or_more);
  }
  if (layOU25_Under_to_layTG_3_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_3) {
    twoCombinations.push_back(layOU25_Under_to_layTG_3_or_more);
  }
  if (layOU35_Under_to_layTG_4_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_4) {
    twoCombinations.push_back(layOU35_Under_to_layTG_4_or_more);
  }
  if (layOU45_Under_to_layTG_5_or_more.hasData() &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) > EventStats::TGEQ_UNKOWN &&
      m_eventStats->getTotalGoalsEquals(event.m_eventId) < EventStats::TGEQ_5) {
    twoCombinations.push_back(layOU45_Under_to_layTG_5_or_more);
  }
}

void BetHandler::findBackLayPositiveOutcome(double p1, double p2,
                                            double price1, double size1,
                                            double price2, double size2) {
  Q_UNUSED(p1);
  Q_UNUSED(p2);
  Q_UNUSED(price1);
  Q_UNUSED(size1);
  Q_UNUSED(price2);
  Q_UNUSED(size2);

  /*
   * takeSize2 > takeSize1
   * takeSize2 < takeSize1 * (takePrice1 -1) / (takePrice2-1)
   * takeSize1 > min(avail1,30.0)
   * takeSize2 > min(avail2,30.0)
   * takeSize1 < avail1
   * takeSize2 < avail2
   *
   * Maximize: f() = -x1 + x2
   *  x1 - x2                       <= 0
   * -x1 + x2*(price1-1)/(price2-1) <= 0
   *  x1                            <= size1
   *       x2                       <= size2
   * -x1                            <= -30
   *      -x2                       <= -30
   * */
}
