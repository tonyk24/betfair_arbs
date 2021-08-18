#include <QDebug>
#include "resmat.h"

ResMat::ResMat()
{
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      m_matrix[row][col] = 0.0;
    }
  }
}

void ResMat::reset()
{
  // Reset
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      m_matrix[row][col] = 0.0;
    }
  }
}

void ResMat::updateResMatPlacedBets(const BfEvent &bfEvent,
                                    const std::list<BetfairMarket> &marketCatalogue,
                                    std::list<std::pair<BfPlaceExecutionReport,BfCurrentOrder> > placedBets)
{
  // Find home and away selectionid
  QStringList sl = bfEvent.m_name.split(" v ");
  QString homeTeamName = sl.at(0);
  QString awayTeamName = sl.at(1);
  qint64 homeSelId = 0;
  qint64 awaySelId = 0;

  for (std::list<BetfairMarket>::const_iterator mit = marketCatalogue.begin();
       mit != marketCatalogue.end(); mit++)
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

  // Update placed bets
  for (std::list<std::pair<BfPlaceExecutionReport,BfCurrentOrder> >::const_iterator it = placedBets.begin();
       it != placedBets.end(); it++)
  {
    for (int row=0; row<8; row++)
    {
      for (int col=0; col<8; col++)
      {
        // MO - Home
        if (it->second.m_selectionId == homeSelId)
        {
          if (row > col)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // MO - Draw
        if (it->second.m_selectionId == 58805)
        {
          if (row == col)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // MO - Away
        if (it->second.m_selectionId == awaySelId)
        {
          if (row < col)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU05 - Over 0.5 goals
        if (it->second.m_selectionId == 5851483)
        {
          if (row+col > 0)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU05 - Under 0.5 goals
        if (it->second.m_selectionId == 5851482)
        {
          if (row+col == 0)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }

        // OU15 - Over 1.5 goals
        if (it->second.m_selectionId == 1221386)
        {
          if (row+col > 1)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU15 - Under 1.5 goals
        if (it->second.m_selectionId == 1221385)
        {
          if (row+col <= 1)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] + (it->second.m_sizeMatched);
          }
        }
        // OU25 - Over 2.5 goals
        if (it->second.m_selectionId == 47973)
        {
          if (row+col > 2)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU25 - Under 2.5 goals
        if (it->second.m_selectionId == 47972)
        {
          if (row+col <= 2)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU35 - Over 3.5 goals
        if (it->second.m_selectionId == 1222345)
        {
          if (row+col > 3)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU35 - Under 3.5 goals
        if (it->second.m_selectionId == 1222345)
        {
          if (row+col <= 3)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU45 - Over 4.5 goals
        if (it->second.m_selectionId == 1222346)
        {
          if (row+col > 4)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU45 - Under 4.5 goals
        if (it->second.m_selectionId == 1222347)
        {
          if (row+col <= 4)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU55 - Over 5.5 goals
        if (it->second.m_selectionId == 1485568)
        {
          if (row+col > 5)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU55 - Under 5.5 goals
        if (it->second.m_selectionId == 1485567)
        {
          if (row+col <= 5)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU65 - Over 6.5 goals
        if (it->second.m_selectionId == 2542449)
        {
          if (row+col > 6)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // OU65 - Under 6.5 goals
        if (it->second.m_selectionId == 2542448)
        {
          if (row+col <= 6)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
          }
        }
        // CS - 0 - 0
        if (it->second.m_selectionId == 1)
        {
          if (row == 0 && col == 0)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 0 - 1
        if (it->second.m_selectionId == 4)
        {
          if (row == 0 && col == 1)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 0 - 2
        if (it->second.m_selectionId == 9)
        {
          if (row == 0 && col == 2)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 0 - 3
        if (it->second.m_selectionId == 16)
        {
          if (row == 0 && col == 3)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 1 - 0
        if (it->second.m_selectionId == 2)
        {
          if (row == 1 && col == 0)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 1 - 1
        if (it->second.m_selectionId == 3)
        {
          if (row == 1 && col == 1)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 1 - 2
        if (it->second.m_selectionId == 8)
        {
          if (row == 1 && col == 2)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 1 - 3
        if (it->second.m_selectionId == 15)
        {
          if (row == 1 && col == 3)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 2 - 0
        if (it->second.m_selectionId == 5)
        {
          if (row == 2 && col == 0)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 2 - 1
        if (it->second.m_selectionId == 6)
        {
          if (row == 2 && col == 1)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 2 - 2
        if (it->second.m_selectionId == 7)
        {
          if (row == 2 && col == 2)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 2 - 3
        if (it->second.m_selectionId == 14)
        {
          if (row == 2 && col == 3)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 3 - 0
        if (it->second.m_selectionId == 10)
        {
          if (row == 3 && col == 0)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 3 - 1
        if (it->second.m_selectionId == 11)
        {
          if (row == 3 && col == 1)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 3 - 2
        if (it->second.m_selectionId == 12)
        {
          if (row == 3 && col == 2)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - 3 - 3
        if (it->second.m_selectionId == 13)
        {
          if (row == 3 && col == 3)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - Any other home win
        if (it->second.m_selectionId == 9063254)
        {
          if (row > 3 && row > col)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - Any other draw
        if (it->second.m_selectionId == 9063256)
        {
          if (row > 3 && col > 3 && row == col)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // CS - Any other away win
        if (it->second.m_selectionId == 9063255)
        {
          if (col > 3 && col > row )
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // TG - 1 or more goals
        if (it->second.m_selectionId == 285469)
        {
          if (row+col >= 1)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // TG - 2 or more goals
        if (it->second.m_selectionId == 285470)
        {
          if (row+col >= 2)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // TG - 3 or more goals
        if (it->second.m_selectionId == 285471)
        {
          if (row+col >= 3)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // TG - 4 or more goals
        if (it->second.m_selectionId == 2795170)
        {
          if (row+col >= 4)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // TG - 5 or more goals
        if (it->second.m_selectionId == 285473)
        {
          if (row+col >= 5)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // TG - 6 or more goals
        if (it->second.m_selectionId == 285474)
        {
          if (row+col >= 6)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
        // TG - 7 or more goals
        if (it->second.m_selectionId == 8215951)
        {
          if (row+col >= 7)
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->second.m_averagePriceMatched-1.0)
                  *it->second.m_sizeMatched;
          }
          else
          {
            if (it->second.m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->second.m_sizeMatched);
            else if (it->second.m_side == BfSide::LAY)
              m_matrix[row][col] += (it->second.m_sizeMatched);
          }
        }
      }
    }
  }
}

void ResMat::updateResMatSimulationBets(const BfEvent &bfEvent,
                                        const std::list<BetfairMarket> &marketCatalogue,
                                        std::list<BfPlaceInstruction> simulatedBets,
                                        std::list<ExtBet> extSimulatedBets)
{
  // Find home and away selectionid
  QStringList sl = bfEvent.m_name.split(" v ");
  QString homeTeamName = sl.at(0);
  QString awayTeamName = sl.at(1);
  qint64 homeSelId = 0;
  qint64 awaySelId = 0;

  for (std::list<BetfairMarket>::const_iterator mit = marketCatalogue.begin();
       mit != marketCatalogue.end(); mit++)
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

  // Update simulated bets
  for (std::list<BfPlaceInstruction>::const_iterator it = simulatedBets.begin();
       it != simulatedBets.end(); it++)
  {

    for (int row=0; row<8; row++)
    {
      for (int col=0; col<8; col++)
      {
        // MO - Home
        if (it->m_selectionId == homeSelId)
        {
          if (row > col)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // MO - Draw
        if (it->m_selectionId == 58805)
        {
          if (row == col)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // MO - Away
        if (it->m_selectionId == awaySelId)
        {
          if (row < col)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU05 - Under 0.5 goals
        if (it->m_selectionId == 5851482)
        {
          if (row+col == 0)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (it->m_limitOrder.m_price-1.0)*it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -= (it->m_limitOrder.m_price-1.0)*it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU05 - Over 0.5 goals
        if (it->m_selectionId == 5851483)
        {
          if (row+col > 0)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (it->m_limitOrder.m_price-1.0)*it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -= (it->m_limitOrder.m_price-1.0)*it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU15 - Over 1.5 goals
        if (it->m_selectionId == 1221386)
        {
          if (row+col > 1)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU15 - Under 1.5 goals
        if (it->m_selectionId == 1221385)
        {
          if (row+col <= 1)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU25 - Over 2.5 goals
        if (it->m_selectionId == 47973)
        {
          if (row+col > 2)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU25 - Under 2.5 goals
        if (it->m_selectionId == 47972)
        {
          if (row+col <= 2)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side  == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side  == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU35 - Over 3.5 goals
        if (it->m_selectionId == 1222345)
        {
          if (row+col > 3)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU35 - Under 3.5 goals
        if (it->m_selectionId == 1222344)
        {
          if (row+col <= 3)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU45 - Over 4.5 goals
        if (it->m_selectionId == 1222346)
        {
          if (row+col > 4)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU45 - Under 4.5 goals
        if (it->m_selectionId == 1222347)
        {
          if (row+col <= 4)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU55 - Over 5.5 goals
        if (it->m_selectionId == 1485568)
        {
          if (row+col > 5)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU55 - Under 5.5 goals
        if (it->m_selectionId == 1485567)
        {
          if (row+col <= 5)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU65 - Over 6.5 goals
        if (it->m_selectionId == 2542449)
        {
          if (row+col > 6)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // OU65 - Under 6.5 goals
        if (it->m_selectionId == 2542448)
        {
          if (row+col <= 6)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 0 - 0
        if (it->m_selectionId == 1)
        {
          if (row == 0 && col == 0)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 0 - 1
        if (it->m_selectionId == 4)
        {
          if (row == 0 && col == 1)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 0 - 2
        if (it->m_selectionId == 9)
        {
          if (row == 0 && col == 2)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 0 - 3
        if (it->m_selectionId == 16)
        {
          if (row == 0 && col == 3)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 1 - 0
        if (it->m_selectionId == 2)
        {
          if (row == 1 && col == 0)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 1 - 1
        if (it->m_selectionId == 3)
        {
          if (row == 1 && col == 1)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 1 - 2
        if (it->m_selectionId == 8)
        {
          if (row == 1 && col == 2)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 1 - 3
        if (it->m_selectionId == 15)
        {
          if (row == 1 && col == 3)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 2 - 0
        if (it->m_selectionId == 5)
        {
          if (row == 2 && col == 0)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 2 - 1
        if (it->m_selectionId == 6)
        {
          if (row == 2 && col == 1)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 2 - 2
        if (it->m_selectionId == 7)
        {
          if (row == 2 && col == 2)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 2 - 3
        if (it->m_selectionId == 14)
        {
          if (row == 2 && col == 3)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 3 - 0
        if (it->m_selectionId == 10)
        {
          if (row == 3 && col == 0)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 3 - 1
        if (it->m_selectionId == 11)
        {
          if (row == 3 && col == 1)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 3 - 2
        if (it->m_selectionId == 12)
        {
          if (row == 3 && col == 2)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - 3 - 3
        if (it->m_selectionId == 13)
        {
          if (row == 3 && col == 3)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - Any other home win
        if (it->m_selectionId == 9063254)
        {
          if (row > 3 && row > col)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - Any other draw
        if (it->m_selectionId == 9063256)
        {
          if (row > 3 && col > 3 && row == col)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // CS - Any other away win
        if (it->m_selectionId == 9063255)
        {
          if (col > 3 && col > row )
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // TG - 1 or more goals
        if (it->m_selectionId == 285469)
        {
          if (row+col >= 1)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // TG - 2 or more goals
        if (it->m_selectionId == 285470)
        {
          if (row+col >= 2)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // TG - 3 or more goals
        if (it->m_selectionId == 285471)
        {
          if (row+col >= 3)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // TG - 4 or more goals
        if (it->m_selectionId == 2795170)
        {
          if (row+col >= 4)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // TG - 5 or more goals
        if (it->m_selectionId == 285473)
        {
          if (row+col >= 5)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // TG - 6 or more goals
        if (it->m_selectionId == 285474)
        {
          if (row+col >= 6)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
        // TG - 7 or more goals
        if (it->m_selectionId == 8215951)
        {
          if (row+col >= 7)
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (it->m_limitOrder.m_price-1.0)
                  *it->m_limitOrder.m_size;
          }
          else
          {
            if (it->m_side == BfSide::BACK)
              m_matrix[row][col] += (-it->m_limitOrder.m_size);
            else if (it->m_side == BfSide::LAY)
              m_matrix[row][col] += (it->m_limitOrder.m_size);
          }
        }
      }
    }
  }

  // ------------------------- Update External simulation bets ---------------------
  for (std::list<ExtBet>::iterator it = extSimulatedBets.begin();
       it != extSimulatedBets.end(); it++)
  {
    for (int row=0; row<8; row++)
    {
      for (int col=0; col<8; col++)
      {
        // MO - Home
        if (it->m_type == ExtBet::MO_Home)
        {
          if (row > col)
          {
            m_matrix[row][col] +=
                (it->m_odds-1.0)
                *it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
        // MO - Draw
        if (it->m_type == ExtBet::MO_Draw)
        {
          if (row == col)
          {
            m_matrix[row][col] +=
                (it->m_odds-1.0)
                *it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
        // MO - Away
        if (it->m_type == ExtBet::MO_Away)
        {
          if (row < col)
          {
            m_matrix[row][col] +=
                (it->m_odds-1.0)
                *it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
        // OU05 - Under 0.5 goals
        if (it->m_type == ExtBet::OU_Under05)
        {
          if (row+col == 0)
          {
            m_matrix[row][col] += (it->m_odds-1.0)*it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
        // OU05 - Over 0.5 goals
        if (it->m_type == ExtBet::OU_Over05)
        {
          if (row+col > 0)
          {
            m_matrix[row][col] += (it->m_odds-1.0)*it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
        // OU15 - Over 1.5 goals
        if (it->m_type == ExtBet::OU_Over15)
        {

          if (row+col > 1)
          {
            m_matrix[row][col] +=
                (it->m_odds-1.0)
                *it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
        // OU15 - Under 1.5 goals
        if (it->m_type == ExtBet::OU_Under15)
        {
          if (row+col <= 1)
          {
            m_matrix[row][col] +=
                (it->m_odds-1.0)
                *it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
        // OU25 - Over 2.5 goals
        if (it->m_type == ExtBet::OU_Over25)
        {
          if (row+col > 2)
          {
            m_matrix[row][col] +=
                (it->m_odds-1.0)
                *it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
        // OU25 - Under 2.5 goals
        if (it->m_type == ExtBet::OU_Under25)
        {
          if (row+col <= 2)
          {
            m_matrix[row][col] +=
                (it->m_odds-1.0)
                *it->m_size;
          }
          else
          {
            m_matrix[row][col] += (-it->m_size);
          }
        }
      }
    }
  }
}

void ResMat::updateResMatLucky(const BfEvent &bfEvent,
                               const std::list<BfArbBet> &arbBets)
{
  // Find home and away selectionid
  QStringList sl = bfEvent.m_name.split(" v ");
  QString homeTeamName = sl.at(0);
  QString awayTeamName = sl.at(1);

  for (std::list<BfArbBet>::const_iterator itArb = arbBets.begin();
       itArb != arbBets.end(); itArb++)
  {
    for (int row=0; row<8; row++)
    {
      for (int col=0; col<8; col++)
      {
        // MO - Home
        if (itArb->m_market.m_marketName == "Match Odds" &&
            itArb->m_selection.m_selectionName == homeTeamName)
        {
          if (row > col)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side  == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // MO - Draw
        if (itArb->m_market.m_marketName == "Match Odds" &&
            itArb->m_pi.m_selectionId == 58805)
        {
          if (row == col)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side  == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // MO - Away
        if (itArb->m_selection.m_selectionName == awayTeamName)
        {
          if (row < col)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side  == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU05 - Under 0.5 goals
        if (itArb->m_pi.m_selectionId == 5851482)
        {
          if (row+col == 0)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_price-1.0)*itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -= (itArb->m_pi.m_limitOrder.m_price-1.0)*itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU05 - Over 0.5 goals
        if (itArb->m_pi.m_selectionId == 5851483)
        {
          if (row+col > 0)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_price-1.0)*itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -= (itArb->m_pi.m_limitOrder.m_price-1.0)*itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU15 - Over 1.5 goals
        if (itArb->m_pi.m_selectionId == 1221386)
        {
          if (row+col > 1)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side  == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU15 - Under 1.5 goals
        if (itArb->m_pi.m_selectionId == 1221385)
        {
          if (row+col <= 1)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU25 - Over 2.5 goals
        if (itArb->m_pi.m_selectionId == 47973)
        {
          if (row+col > 2)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side  == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU25 - Under 2.5 goals
        if (itArb->m_pi.m_selectionId == 47972)
        {
          if (row+col <= 2)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side  == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side  == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU35 - Over 3.5 goals
        if (itArb->m_pi.m_selectionId == 1222345)
        {
          if (row+col > 3)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU35 - Under 3.5 goals
        if (itArb->m_pi.m_selectionId == 1222344)
        {
          if (row+col <= 3)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU45 - Over 4.5 goals
        if (itArb->m_pi.m_selectionId == 1222346)
        {
          if (row+col > 4)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU45 - Under 4.5 goals
        if (itArb->m_pi.m_selectionId == 1222347)
        {
          if (row+col <= 4)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU55 - Over 5.5 goals
        if (itArb->m_pi.m_selectionId == 1485568)
        {
          if (row+col > 5)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU55 - Under 5.5 goals
        if (itArb->m_pi.m_selectionId == 1485567)
        {
          if (row+col <= 5)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU65 - Over 6.5 goals
        if (itArb->m_pi.m_selectionId == 2542449)
        {
          if (row+col > 6)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // OU65 - Under 6.5 goals
        if (itArb->m_pi.m_selectionId == 2542448)
        {
          if (row+col <= 6)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS 0-0
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 1)
        {
          if (row+col == 0)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 0 - 1
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 4)
        {
          if (row == 0 && col == 1)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 0 - 2
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 9)
        {
          if (row == 0 && col == 2)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 0 - 3
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 16)
        {
          if (row == 0 && col == 3)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 1 - 0
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 2)
        {
          if (row == 1 && col == 0)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 1 - 1
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 3)
        {
          if (row == 1 && col == 1)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 1 - 2
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 8)
        {
          if (row == 1 && col == 2)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 1 - 3
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 15)
        {
          if (row == 1 && col == 3)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 2 - 0
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 5)
        {
          if (row == 2 && col == 0)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 2 - 1
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 6)
        {
          if (row == 2 && col == 1)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 2 - 2
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 7)
        {
          if (row == 2 && col == 2)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 2 - 3
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 14)
        {
          if (row == 2 && col == 3)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 3 - 0
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 10)
        {
          if (row == 3 && col == 0)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 3 - 1
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 11)
        {
          if (row == 3 && col == 1)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 3 - 2
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 12)
        {
          if (row == 3 && col == 2)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // CS - 3 - 3
        if (itArb->m_market.m_marketName == "Correct Score" &&
            itArb->m_pi.m_selectionId == 13)
        {
          if (row == 3 && col == 3)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // TG - 1 or more goals
        if (itArb->m_market.m_marketName == "Total Goals" &&
            itArb->m_pi.m_selectionId == 285469)
        {
          if (row+col >= 1)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // TG - 2 or more goals
        if (itArb->m_market.m_marketName == "Total Goals" &&
            itArb->m_pi.m_selectionId == 285470)
        {
          if (row+col >= 2)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // TG - 3 or more goals
        if (itArb->m_market.m_marketName == "Total Goals" &&
            itArb->m_pi.m_selectionId == 285471)
        {
          if (row+col >= 3)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // TG - 4 or more goals
        if (itArb->m_market.m_marketName == "Total Goals" &&
            itArb->m_pi.m_selectionId == 2795170)
        {
          if (row+col >= 4)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // TG - 5 or more goals
        if (itArb->m_market.m_marketName == "Total Goals" &&
            itArb->m_pi.m_selectionId == 285473)
        {
          if (row+col >= 5)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // TG - 6 or more goals
        if (itArb->m_market.m_marketName == "Total Goals" &&
            itArb->m_pi.m_selectionId == 285474)
        {
          if (row+col >= 6)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
        // TG - 7 or more goals
        if (itArb->m_market.m_marketName == "Total Goals" &&
            itArb->m_pi.m_selectionId == 8215951)
        {
          if (row+col >= 7)
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] +=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] -=
                  (itArb->m_pi.m_limitOrder.m_price-1.0)
                  *itArb->m_pi.m_limitOrder.m_size;
          }
          else
          {
            if (itArb->m_pi.m_side == BfSide::BACK)
              m_matrix[row][col] += (-itArb->m_pi.m_limitOrder.m_size);
            else if (itArb->m_pi.m_side == BfSide::LAY)
              m_matrix[row][col] += (itArb->m_pi.m_limitOrder.m_size);
          }
        }
      }
    }
  }
}

  double ResMat::getItemData(int row, int column)
  {
    return m_matrix[row][column];
  }
