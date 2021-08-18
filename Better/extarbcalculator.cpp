#include <cmath>
#include "extarbcalculator.h"
#include "models/currentbetsmodellisttype.h"

ExtArbCalculator::ExtArbCalculator()
{

}

bool ExtArbCalculator::chooseBets(const BfEvent &event,
                               std::vector<CurrentBetsModelListType> &data,
                               double bfMaxExposure)
{

  QStringList sl = event.m_name.split(" v ");
  QString homeTeamName = sl.at(0);
  QString awayTeamName = sl.at(1);

  for (std::vector<CurrentBetsModelListType>::iterator itData = data.begin();
       itData != data.end(); itData++)
  {
    // MO HOME
    if ((itData->m_bfMarket.m_marketName == "Match Odds" &&
         itData->m_extBet.m_type == ExtBet::MO_Home &&
         itData->m_bfSelection.m_selectionName == homeTeamName &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
        // MO DRAW
        (itData->m_bfMarket.m_marketName == "Match Odds" &&
         itData->m_extBet.m_type == ExtBet::MO_Draw &&
         itData->m_bfSelection.m_selectionId == 58805 &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
        // MO AWAY
        (itData->m_bfMarket.m_marketName == "Match Odds" &&
         itData->m_extBet.m_type == ExtBet::MO_Away &&
         itData->m_bfSelection.m_selectionName == awayTeamName &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
        // OU05 Over0.5
        (itData->m_bfMarket.m_marketName == "Over/Under 0.5 Goals" &&
         itData->m_extBet.m_type == ExtBet::OU_Over05 &&
         itData->m_bfSelection.m_selectionId == 5851483 &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
        // OU05 Over0.5
        (itData->m_bfMarket.m_marketName == "Over/Under 0.5 Goals" &&
         itData->m_extBet.m_type == ExtBet::OU_Under05 &&
         itData->m_bfSelection.m_selectionId == 5851482 &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
        // OU05 Over1.5
        (itData->m_bfMarket.m_marketName == "Over/Under 1.5 Goals" &&
         itData->m_extBet.m_type == ExtBet::OU_Over15 &&
         itData->m_bfSelection.m_selectionId == 1221386 &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
        // OU05 Over1.5
        (itData->m_bfMarket.m_marketName == "Over/Under 1.5 Goals" &&
         itData->m_extBet.m_type == ExtBet::OU_Under15 &&
         itData->m_bfSelection.m_selectionId == 1221385 &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
        // OU05 Over2.5
        (itData->m_bfMarket.m_marketName == "Over/Under 2.5 Goals" &&
         itData->m_extBet.m_type == ExtBet::OU_Over25 &&
         itData->m_bfSelection.m_selectionId == 47973 &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
        // OU05 Over2.5
        (itData->m_bfMarket.m_marketName == "Over/Under 2.5 Goals" &&
         itData->m_extBet.m_type == ExtBet::OU_Under25 &&
         itData->m_bfSelection.m_selectionId == 47972 &&
         itData->m_bfSelection.m_availableToLayPrice.size() > 0)
        )
    {
      //qDebug() << "---------------------------------------";
      //qDebug() << "marketName: " << itData->m_bfMarket.m_marketName;
      //qDebug() << "type: " << ExtBet::toTypeStr(itData->m_extBet.m_type);
      //qDebug() << "selId= " << itData->m_bfSelection.m_selectionId;
      //qDebug() << "availLayPrice= " << itData->m_bfSelection.m_availableToLayPrice.size();
      // Example
      // Ext back bet price       = 3.10
      // Ext max exposure size    = 100.0
      // Ext size                 = 100.0
      // Betfair lay bet price    = 2.9
      // Betfair lay size         = 3000.0
      // Betfair lay max exposure = 100.0
      double extPrice = itData->m_extBet.m_odds;
      double extSize = itData->m_extBet.m_size;

      //qDebug() << "extPrice= " << itData->m_extBet.m_odds;
      //qDebug() << "extSize= " << itData->m_extBet.m_size;

      double bfPrice = itData->m_bfSelection.m_availableToLayPrice.front();
      //qDebug() << "bfPrice=" << QString::number(itData->m_bfSelection.m_availableToLayPrice.front());

      double p1 = 1.0/extPrice;            // 1.0/3.10      = 0.32258
      double p2_lay = 1.0 - (1.0/bfPrice); // 1- (1/2.9)    = 0.65517
      QString result;

      //qDebug() << "Chance= " + QString::number(p1+p2_lay);


      double p1_norm = p1/(p1+p2_lay);    //  0.32258/(0.32258+0.65517) = 0.3992
      double p2_norm = p2_lay/(p1+p2_lay); // 0.65517/(0.32258+0.65517) = 0.6700

      double impliedMaxExposure2 = ((bfMaxExposure*(bfPrice-1)) / (bfPrice-1.0)) / p2_norm;
      // (2.9-1.0) * 3000.0 / 0.6700 = 8507.46

      double localMaxExposure = impliedMaxExposure2;
      // = 100.0

      double takePrice1 = extPrice;
      double takeSize1 = localMaxExposure * p1_norm;
      // takeSize1 = 100.0 * 0.3992 = 39.92
      double takePrice2 = bfPrice;
      double takeSize2 = 0.0;
      double maxExposure2 = localMaxExposure * p2_norm;
      takeSize2 = maxExposure2 / (takePrice2-1.0);
      takeSize2 = round( takeSize2 * 10.0 ) / 10.0;
      // takeSize2 = 67.0
      double outcome1 = 0.0;
      double outcome2 = 0.0;
      if (p1+p2_lay < 0.97) { // 0.32258+0.65517 = 0.977753 OK!

        outcome1 = (takePrice1-1.0)*takeSize1 - (takePrice2-1.0)*takeSize2;
        outcome2 = -takeSize1+takeSize2;
        result = "bfSize =" + QString::number(takeSize1) + "extSize= " + QString::number(takeSize2);
      }
      else
      {
        outcome1 = (takePrice1-1.0)*takeSize1 - (takePrice2-1.0)*takeSize2;
        outcome2 = -takeSize1+takeSize2;
        result = "Chance= " + QString::number(p1+p2_lay);
      }
      itData->m_extBet.m_outCome1 = outcome1;
      itData->m_extBet.m_outCome2 = outcome2;
      itData->m_extBet.m_arbResult = result;
    }
  }

  /*
  // Find home and away selection id
  for (std::list<BetfairMarket>::const_iterator mit = markets.begin();
       mit != markets.end(); mit++)
  {
    for(std::list<BetfairSelection>::const_iterator sit = mit->m_selections.begin();
        sit != mit->m_selections.end(); sit++)
    {
      if (sit->m_selectionName == homeTeamName)
        homeSelId = sit->m_selectionId;
      if (sit->m_selectionName == awayTeamName)
        awaySelId = sit->m_selectionId;
    }
  }

  // Find book data
  for (std::list<ExtBet>::iterator itExtBet = extBets.begin();
       itExtBet != extBets.end(); itExtBet++)
  {
    for (std::list<BetfairMarket>::const_iterator itMarketBook = markets.begin();
         itMarketBook != markets.end(); itMarketBook++) {
      for (std::list<BetfairSelection>::const_iterator itSelBook = itData->m_bfMarket.m_selections.begin();
           itSelBook != itData->m_bfMarket.m_selections.end(); itSelBook++)
      {
        // MO HOME
        if ((itData->m_bfMarket.m_marketName == "Match Odds" &&
             itData->m_extBet.m_type == ExtBet::MO_Home &&
             itData->m_bfSelection.m_selectionId == homeSelId &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
            // MO DRAW
            (itData->m_bfMarket.m_marketName == "Match Odds" &&
             itData->m_extBet.m_type == ExtBet::MO_Draw &&
             itData->m_bfSelection.m_selectionId == 58805 &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
            // MO AWAY
            (itData->m_bfMarket.m_marketName == "Match Odds" &&
             itData->m_extBet.m_type == ExtBet::MO_Away &&
             itData->m_bfSelection.m_selectionId == awaySelId &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
            // OU05 Over0.5
            (itData->m_bfMarket.m_marketName == "Over/Under 0.5 Goals" &&
             itData->m_extBet.m_type == ExtBet::OU_Over05 &&
             itData->m_bfSelection.m_selectionId == 5851483 &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
            // OU05 Over0.5
            (itData->m_bfMarket.m_marketName == "Over/Under 0.5 Goals" &&
             itData->m_extBet.m_type == ExtBet::OU_Under05 &&
             itData->m_bfSelection.m_selectionId == 5851482 &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
            // OU05 Over1.5
            (itData->m_bfMarket.m_marketName == "Over/Under 1.5 Goals" &&
             itData->m_extBet.m_type == ExtBet::OU_Over15 &&
             itData->m_bfSelection.m_selectionId == 1221386 &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
            // OU05 Over1.5
            (itData->m_bfMarket.m_marketName == "Over/Under 1.5 Goals" &&
             itData->m_extBet.m_type == ExtBet::OU_Under15 &&
             itData->m_bfSelection.m_selectionId == 1221385 &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
            // OU05 Over2.5
            (itData->m_bfMarket.m_marketName == "Over/Under 2.5 Goals" &&
             itData->m_extBet.m_type == ExtBet::OU_Over25 &&
             itData->m_bfSelection.m_selectionId == 47973 &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0) ||
            // OU05 Over2.5
            (itData->m_bfMarket.m_marketName == "Over/Under 2.5 Goals" &&
             itData->m_extBet.m_type == ExtBet::OU_Under25 &&
             itData->m_bfSelection.m_selectionId == 47972 &&
             itData->m_bfSelection.m_availableToLayPrice.size() > 0)
            )
        {
          // Example
          // Ext back bet price       = 3.10
          // Ext max exposure size    = 100.0
          // Ext size                 = 100.0
          // Betfair lay bet price    = 2.9
          // Betfair lay size         = 3000.0
          // Betfair lay max exposure = 100.0
          double extPrice = itData->m_extBet.m_odds;
          double extSize = itData->m_extBet.m_size;

          //qDebug() << "extPrice= " << itData->m_extBet.m_odds;
          //qDebug() << "extSize= " << itData->m_extBet.m_size;

          double bfPrice = itData->m_bfSelection.m_availableToLayPrice.front();
          //qDebug() << "bfPrice=" << QString::number(itData->m_bfSelection.m_availableToLayPrice.front());

          double p1 = 1.0/extPrice;            // 1.0/3.10      = 0.32258
          double p2_lay = 1.0 - (1.0/bfPrice); // 1- (1/2.9)    = 0.65517
          QString result;

          //qDebug() << "Chance= " + QString::number(p1+p2_lay);


          double p1_norm = p1/(p1+p2_lay);    //  0.32258/(0.32258+0.65517) = 0.3992
          double p2_norm = p2_lay/(p1+p2_lay); // 0.65517/(0.32258+0.65517) = 0.6700

          double impliedMaxExposure2 = ((bfMaxExposure*(bfPrice-1)) / (bfPrice-1.0)) / p2_norm;
          // (2.9-1.0) * 3000.0 / 0.6700 = 8507.46

          double localMaxExposure = impliedMaxExposure2;
          // = 100.0

          double takePrice1 = extPrice;
          double takeSize1 = localMaxExposure * p1_norm;
          // takeSize1 = 100.0 * 0.3992 = 39.92
          double takePrice2 = bfPrice;
          double takeSize2 = 0.0;
          double maxExposure2 = localMaxExposure * p2_norm;
          takeSize2 = maxExposure2 / (takePrice2-1.0);
          takeSize2 = round( takeSize2 * 10.0 ) / 10.0;
          // takeSize2 = 67.0
          double outcome1 = 0.0;
          double outcome2 = 0.0;
          if (p1+p2_lay < 0.97) { // 0.32258+0.65517 = 0.977753 OK!

            outcome1 = (takePrice1-1.0)*takeSize1 - (takePrice2-1.0)*takeSize2;
            outcome2 = -takeSize1+takeSize2;
            result = "bfSize =" + QString::number(takeSize1) + "extSize= " + QString::number(takeSize2);
          }
          else
          {
            outcome1 = (takePrice1-1.0)*takeSize1 - (takePrice2-1.0)*takeSize2;
            outcome2 = -takeSize1+takeSize2;
            result = "Chance= " + QString::number(p1+p2_lay);
          }
          itData->m_extBet.m_outCome1 = outcome1;
          itData->m_extBet.m_outCome2 = outcome2;
          itData->m_extBet.m_arbResult = result;
        }
      }
    }
  }
  */

  return true;
}
