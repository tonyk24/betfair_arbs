#include <cmath>
#include <QDebug>
#include <QColor>
#include "currentbetsmodel.h"

#include "bftypes/bfmarket.h"
#include "types/extbet.h"

CurrentBetsModel::CurrentBetsModel(QObject *parent, BfEvent bfEvent)
  :QAbstractTableModel(parent),
    m_hasArbitrageBets(false),
    m_bfEvent(bfEvent)
{
}

int CurrentBetsModel::rowCount(const QModelIndex & /*parent*/) const
{
  return m_data.size()*2;
}

int CurrentBetsModel::columnCount(const QModelIndex & /*parent*/) const
{
  return 18;
}

Qt::ItemFlags CurrentBetsModel::flags(const QModelIndex & index) const
{
  if(index.column() == 10 || index.column() == 14)
    return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
  return QAbstractTableModel::flags(index);
}

QVariant CurrentBetsModel::data(const QModelIndex &index, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (index.column() == 0)
      return m_data[index.row()/2].m_bfMarket.m_marketId;
    else if (index.column() == 1)
      return m_data[index.row()/2].m_bfMarket.m_marketName;
    else if (index.column() == 2)
      return BfMarketStatus::toStr(m_data[index.row()/2].m_bfMarket.m_marketStatus);
    else if (index.column() == 3)
      return QString::number(m_data[index.row()/2].m_bfSelection.m_selectionId);
    else if (index.column() == 4)
      return QString::number(m_data[index.row()/2].m_bfSelection.m_handicap);
    else if (index.column() == 5)
      return m_data[index.row()/2].m_bfSelection.m_selectionName;
    else if (index.column() == 6)
      return m_data[index.row()/2].m_bfSelection.m_status;
    else if (index.column() == 7)
    {
      if (index.row()%2 == 0)
      {
        if (m_data[index.row()/2].m_bfSelection.m_availableToBackPrice.size() > 0)
          return QString::number(m_data[index.row()/2].m_bfSelection.m_availableToBackPrice.front());
        else
          return "NA";
      }
      else
      {
        if (m_data[index.row()/2].m_bfSelection.m_availableToLayPrice.size() > 0)
          return QString::number(m_data[index.row()/2].m_bfSelection.m_availableToLayPrice.front());
        else
          return "NA";
      }
    }
    else if (index.column() == 8)
    {
      if (index.row()%2 == 0)
      {
        if (m_data[index.row()/2].m_bfSelection.m_availableToBackSize.size() > 0)
          return QString::number(m_data[index.row()/2].m_bfSelection.m_availableToBackSize.front());
        else
          return "NA";
      }
      else
      {
        if (m_data[index.row()/2].m_bfSelection.m_availableToLaySize.size() > 0)
          return QString::number(m_data[index.row()/2].m_bfSelection.m_availableToLaySize.front());
        else
          return "NA";
      }
    }
    else if (index.column() == 9)
    {
      if (index.row()%2 == 0)
      {
        if (m_data[index.row()/2].m_bfSelection.m_availableToBackSize.size() > 0)
          return QString::number(m_maxExposure);
        else
          return "NA";
      }
      else
      {
        if (m_data[index.row()/2].m_bfSelection.m_availableToLaySize.size() > 0)
        {

          return QString::number(m_data[index.row()/2].m_simLaySize);
        }
        else
        {
          return "NA";
        }
      }
    }
    else if (index.column() == 10)
    {
      if (index.row()%2 == 0)
        return QString("Back");
      else
        return QString("Lay");
    }
    else if (index.column() == 12 && index.row()%2 == 1)
    {
      if (m_data[index.row()/2].m_extBet.m_type == ExtBet::NONE)
        return QString("");
      else
        return QString::number(m_data[index.row()/2].m_extBet.m_odds);
    }
    else if (index.column() == 13 && index.row()%2 == 1)
    {
      if (m_data[index.row()/2].m_extBet.m_type == ExtBet::NONE)
        return QString("");
      else
        return QString::number(m_data[index.row()/2].m_extBet.m_size);
    }
    else if (index.column() == 14)
    {
      if (index.row()%2 == 1)
        return QString("Back");
      else
        return QString("");
    }
    else if (index.column() == 15 && index.row()%2 == 1)
    {
      if (m_data[index.row()/2].m_extBet.m_type == ExtBet::NONE)
        return QString("");
      else
        return QString::number(m_data[index.row()/2].m_extBet.m_outCome1);
    }
    else if (index.column() == 16 && index.row()%2 == 1)
    {
      if (m_data[index.row()/2].m_extBet.m_type == ExtBet::NONE)
        return QString("");
      else
        return QString::number(m_data[index.row()/2].m_extBet.m_outCome2);
    }
    else if (index.column() == 17 && index.row()%2 == 1)
    {
      if (m_data[index.row()/2].m_extBet.m_type == ExtBet::NONE)
        return QString("");
      else
        return m_data[index.row()/2].m_extBet.m_arbResult;
    }

  }
  else if (role == Qt::CheckStateRole)  // this shows the checkbox
  {
    if (index.column() == 10)
    {
      if (index.row()%2 == 0)
        return m_data[index.row()/2].m_simBfBack?Qt::Checked:Qt::Unchecked;
      else
        return m_data[index.row()/2].m_simBfLay?Qt::Checked:Qt::Unchecked;
    }
    else if(index.column() == 14)
    {
      if (index.row()%2 == 1)
        return m_data[index.row()/2].m_extBet.m_simulate?Qt::Checked:Qt::Unchecked;
    }

  }
  else if (role == Qt::BackgroundColorRole) {
    if (index.row()%2 == 1 &&
        m_data[index.row()/2].m_extBet.m_outCome1 > 0.0 &&
        m_data[index.row()/2].m_extBet.m_outCome2 > 0.0)
    {
      return QColor(Qt::green);
    }
    else if (index.row()%4 == 0 || index.row()%4 == 1)
      return QColor(Qt::gray);
    else
      return QColor::fromRgb(255,255,255);
  }
  return QVariant();
}

QVariant CurrentBetsModel::headerData(int section, Qt::Orientation orientation, int role) const
{

  if(role == Qt::DisplayRole)
  {
    if(orientation == Qt::Horizontal)
    {
      if (section == 0)
        return QString("mid");
      else if (section == 1)
        return QString("mName");
      else if (section == 2)
        return QString("mstatus");
      else if (section == 3)
        return QString("sid");
      else if (section == 4)
        return QString("handicap");
      else if (section == 5)
        return QString("sName");
      else if (section == 6)
        return QString("sStatus");
      else if (section == 7)
        return QString("Price");
      else if (section == 8)
        return QString("Size");
      else if (section == 9)
        return QString("SimSize");
      else if (section == 10)
        return QString("Sim");
      else if (section == 11)
        return QString("Place");
      else if (section == 12)
        return QString("Odds");
      else if (section == 13)
        return QString("Size");
      else if (section == 14)
        return QString("Simulate");
      else if (section == 15)
        return QString("Outcome1");
      else if (section == 16)
        return QString("Outcome2");
      else if (section == 17)
        return QString("Result");
    }

  }

  return QVariant::Invalid;
}

void CurrentBetsModel::setMarketData(std::list<BetfairMarket> marketData)
{
  QStringList sl = m_bfEvent.m_name.split(" v ");
  QString homeTeamName = sl.at(0);
  QString awayTeamName = sl.at(1);

  for (std::list<BetfairMarket>::iterator itMarket = marketData.begin();
       itMarket != marketData.end(); itMarket++)
  {
    for (std::list<BetfairSelection>::iterator itSel = itMarket->m_selections.begin();
         itSel != itMarket->m_selections.end(); itSel++)
    {
      bool found = false;
      for (std::vector<CurrentBetsModelListType>::iterator itData= m_data.begin();
           itData != m_data.end(); itData++)
      {
        if (itData->m_bfMarket.m_marketId == itMarket->m_marketId &&
            itData->m_bfSelection.m_selectionId == itSel->m_selectionId)
        {
          itData->m_bfSelection = *itSel;
          itData->m_bfMarket = *itMarket;

          if (itData->m_bfSelection.m_availableToLaySize.size() > 0 &&
              itData->m_bfSelection.m_availableToLayPrice.size() > 0)
          {
            // Simulate bf size
            itData->m_simLaySize = m_maxExposure / (itData->m_bfSelection.m_availableToLayPrice.front()-1.0);
            itData->m_simLaySize = round( itData->m_simLaySize * 10.0 ) / 10.0;

            // Simulate ext size
            if (itData->m_extBet.m_odds > 0.0)
            {
              double size = (itData->m_bfSelection.m_availableToLayPrice.front()
                             *itData->m_simLaySize) / itData->m_extBet.m_odds;
              size = round( size * 10.0 ) / 10.0;
              itData->m_extBet.m_size = size;
            }
          }
          else
            itData->m_simLaySize = 0.0;
          found = true;
          break;
        }
      }

      if(!found)
      {
        if (itSel->m_selectionName == homeTeamName)
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::MO_Home)));
        else if (itSel->m_selectionName == awayTeamName)
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::MO_Away)));
        else if (itSel->m_selectionName == "The Draw")
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::MO_Draw)));
        else if (itSel->m_selectionName == "Over 0.5 Goals")
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::OU_Over05)));
        else if (itSel->m_selectionName == "Under 0.5 Goals")
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::OU_Under05)));
        else if (itSel->m_selectionName == "Over 1.5 Goals")
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::OU_Over15)));
        else if (itSel->m_selectionName == "Under 1.5 Goals")
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::OU_Under15)));
        else if (itSel->m_selectionName == "Over 2.5 Goals")
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::OU_Over25)));
        else if (itSel->m_selectionName == "Under 2.5 Goals")
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::OU_Under25)));
        else
          m_data.push_back(CurrentBetsModelListType(*itMarket,
                                                    *itSel,
                                                    ExtBet(ExtBet::NONE)));
      }
    }
  }

  ExtArbCalculator::chooseBets(m_bfEvent,m_data, m_maxExposure);

  QModelIndex topLeft = index(0, 0);
  QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

  emit dataChanged(topLeft, bottomRight);
  emit layoutChanged();

  checkForArbitrageExistance();
}

void CurrentBetsModel::updateSPOdds(ExtSiteSPOdds odds)
{
  //setItem(0, 2, new QTableWidgetItem(QString::number(odds.m_homeOdds)));
  //setItem(1, 2, new QTableWidgetItem(QString::number(odds.m_awayOdds)));
  //setItem(2, 2, new QTableWidgetItem(QString::number(odds.m_drawOdds)));

  QStringList sl = m_bfEvent.m_name.split(" v ");
  QString homeTeamName = sl.at(0);
  QString awayTeamName = sl.at(1);

  for (std::vector<CurrentBetsModelListType>::iterator itData= m_data.begin();
       itData != m_data.end(); itData++)
  {
    if (itData->m_bfSelection.m_selectionName == homeTeamName)
    {
      itData->m_extBet.m_type = ExtBet::MO_Home;
      itData->m_extBet.m_odds = odds.m_homeOdds;
    }
    else if (itData->m_bfSelection.m_selectionName == "The Draw")
    {
      itData->m_extBet.m_type = ExtBet::MO_Draw;
      itData->m_extBet.m_odds = odds.m_drawOdds;
    }
    else if (itData->m_bfSelection.m_selectionName == awayTeamName)
    {
      itData->m_extBet.m_type = ExtBet::MO_Away;
      itData->m_extBet.m_odds = odds.m_awayOdds;
    }

    if (itData->m_bfSelection.m_availableToLaySize.size() > 0 &&
        itData->m_bfSelection.m_availableToLayPrice.size() > 0 &&
        itData->m_extBet.m_odds > 0.0)
    {
      double size = (itData->m_bfSelection.m_availableToLayPrice.front()
                     *itData->m_simLaySize) / itData->m_extBet.m_odds;
      size = round( size * 10.0 ) / 10.0;
      itData->m_extBet.m_size = size;
    }
    else
    {
      itData->m_extBet.m_size = 0.0;
    }
  }

  ExtArbCalculator::chooseBets(m_bfEvent,m_data, m_maxExposure);

  QModelIndex topLeft = index(0, 0);
  QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

  emit dataChanged(topLeft, bottomRight);
  emit layoutChanged();

  checkForArbitrageExistance();
}

bool CurrentBetsModel::flipCheckState(const QModelIndex &index)
{
  bool ret = false;
  //qDebug() << "flipCheckState" << index;
  if (index.column() == 10)
  {
    if (index.row()%2 == 0)
    {
      m_data[index.row()/2].m_simBfBack = !m_data[index.row()/2].m_simBfBack;
      ret= m_data[index.row()/2].m_simBfBack;
    }
    else
    {
      m_data[index.row()/2].m_simBfLay = !m_data[index.row()/2].m_simBfLay;
      ret = m_data[index.row()/2].m_simBfLay;
    }
  }
  emit dataChanged(index, index);
  return ret;
}

bool CurrentBetsModel::flipExtCheckState(const QModelIndex &index)
{
  bool ret = false;
  //qDebug() << "flipCheckState" << index;
  if (index.column() == 14)
  {
    if (index.row()%2 == 1)
    {
      m_data[index.row()/2].m_extBet.m_simulate = !m_data[index.row()/2].m_extBet.m_simulate;
      ret = m_data[index.row()/2].m_extBet.m_simulate;
    }
  }
  emit dataChanged(index, index);
  return ret;
}

CurrentBetsModelListType CurrentBetsModel::getDataForRow(int row)
{
  return m_data[row/2];
}

void CurrentBetsModel::checkForArbitrageExistance()
{
  bool ret = false;
  for (std::vector<CurrentBetsModelListType>::iterator itData= m_data.begin();
       itData != m_data.end(); itData++)
  {
    if (itData->m_extBet.m_outCome1 > 0.0 &&
        itData->m_extBet.m_outCome2 > 0.0)
    {
      ret = true;
    }
  }

  if (ret != m_hasArbitrageBets)
    emit hasAribtrageBetsChanged(ret);

  m_hasArbitrageBets = ret;
}
