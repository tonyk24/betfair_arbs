#include "bfbetstablewidget.h"

#include <cmath>

#include <QDebug>
#include <QPushButton>

#include "bfenums/bfside.h"


BfBetsTableView::BfBetsTableView(QWidget *parent, BfEvent bfEvent) :
  QTableView(parent),
  m_bfEvent(bfEvent)
{



  m_signalMapper = new QSignalMapper(this);

  m_model = new CurrentBetsModel(this,bfEvent);
  setModel(m_model);

  setColumnWidth(2,60); // mStatus
  setColumnWidth(4,20); // handicap
  setColumnWidth(7,60); // Price
  setColumnWidth(8,60); // Size
  setColumnWidth(9,60); // SimSize
  setColumnWidth(17, 400);

  connect(this, SIGNAL(clicked(QModelIndex)),
          this,SLOT(on_pushButtonSimulate_checked(QModelIndex)));
  connect(m_model, SIGNAL(hasAribtrageBetsChanged(bool)),
          this, SLOT(receivedAribtrageBetsChanged(bool)));

}

void BfBetsTableView::updateMaxExposure(double maxExposure)
{
  m_maxExposure = maxExposure;
  m_model->setMaxExposure(maxExposure);
}


void BfBetsTableView::receivedMarketData(std::list<BfLib::BetfairMarket> marketBook)
{
  m_model->setMarketData(marketBook);
  delete m_signalMapper;
  m_signalMapper = new QSignalMapper(this);
  for (int row = 0; row<m_model->rowCount(); row++)
  {
    //make new button for this row
    QModelIndex index = m_model->index(row, 11);
    QPushButton *placeButton = new QPushButton("Place");
    this->setIndexWidget(index, placeButton);

    m_signalMapper->setMapping(placeButton, row);
    connect(placeButton, SIGNAL(clicked(bool)), m_signalMapper, SLOT(map()));
  }
  connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(on_pushButtonPlace_clicked(int)));
}

void BfBetsTableView::updateSPOdds(ExtSiteSPOdds odds)
{
  m_model->updateSPOdds(odds);
}

void BfBetsTableView::receivedAribtrageBetsChanged(bool hasArbBets)
{
  emit hasAribtrageBetsChanged(hasArbBets);
}

void BfBetsTableView::on_pushButtonSimulate_checked(QModelIndex index)
{

  CurrentBetsModelListType cbmlt= m_model->getDataForRow(index.row());


  //qDebug() << "SimulateBack pressed from row: " << QString::number(index.row()) << ", column= " << index.column();
  if (index.column() == 10)
  {
    //qDebug() << "on_pushButtonSimulate_checked";
    bool currentCheckState = this->m_model->flipCheckState(index);
    //qDebug() << "currentCheckState = " << currentCheckState;

    if (index.row()%2 == 0) // Back
    {
      emit placeBetSimulatedRemove(cbmlt.m_bfMarket.m_marketId,
                                   cbmlt.m_bfSelection.m_selectionId,
                                   cbmlt.m_bfSelection.m_handicap,
                                   BfSide::BACK);
      if (currentCheckState)
      {
        double takeSize = m_maxExposure;
        if (cbmlt.m_bfSelection.m_availableToBackPrice.size() > 0)
        {
          //qDebug() << "takeSize" << takeSize;
          emit placeBetSimulated(cbmlt.m_bfMarket.m_marketId,
                                 cbmlt.m_bfSelection.m_selectionId,
                                 cbmlt.m_bfSelection.m_handicap,
                                 BfSide::BACK,
                                 cbmlt.m_bfSelection.m_availableToBackPrice.front(),
                                 takeSize);
        }
      }
    }
    else // Lay
    {
      emit placeBetSimulatedRemove(cbmlt.m_bfMarket.m_marketId,
                                   cbmlt.m_bfSelection.m_selectionId,
                                   cbmlt.m_bfSelection.m_handicap,
                                   BfSide::LAY);
      if (currentCheckState)
      {
        double takeSize = cbmlt.m_simLaySize;
        //qDebug() << "takeSize" << takeSize;
        if (cbmlt.m_bfSelection.m_availableToLayPrice.size() > 0)
        {
          //qDebug() << "takeSize" << takeSize;
          emit placeBetSimulated(cbmlt.m_bfMarket.m_marketId,
                                 cbmlt.m_bfSelection.m_selectionId,
                                 cbmlt.m_bfSelection.m_handicap,
                                 BfSide::LAY,
                                 cbmlt.m_bfSelection.m_availableToLayPrice.front(),
                                 takeSize);
        }
      }
    }
  }
  else if (index.column() == 14)
  {
    emit placeExtBetSimulatedRemoved(cbmlt.m_extBet);
    bool currentCheckState = this->m_model->flipExtCheckState(index);

    if (currentCheckState)
    {
      emit placeExtBetSimulated(cbmlt.m_extBet);
    }
  }
}

void BfBetsTableView::on_pushButtonPlace_clicked(int row)
{
  qDebug() << "on_pushButtonPlace_clicked: " << row;
  CurrentBetsModelListType cbmlt= m_model->getDataForRow(row);
  if (row%2 == 0) // Back
  {
    qDebug() << "Place pressed from row: " << QString::number(row);
    qDebug() << "mid" << cbmlt.m_bfMarket.m_marketId;
    qDebug() << "sid" << cbmlt.m_bfSelection.m_selectionId;
    qDebug() << "handicap" << cbmlt.m_bfSelection.m_handicap;
    qDebug() << "side" << BfSide::toStr(BfSide::BACK);
    if (cbmlt.m_bfSelection.m_availableToBackPrice.size() > 0 &&
        cbmlt.m_bfSelection.m_availableToBackSize.size())
    {
      qDebug() << "takePrice" << cbmlt.m_bfSelection.m_availableToBackPrice.front();
      double takeSize = m_maxExposure;
      if (cbmlt.m_bfSelection.m_availableToBackSize.front() < takeSize)
        takeSize = cbmlt.m_bfSelection.m_availableToBackSize.front();
      qDebug() << "takeSize" << takeSize;

      emit placeBet(cbmlt.m_bfMarket.m_marketId,
                    cbmlt.m_bfSelection.m_selectionId,
                    cbmlt.m_bfSelection.m_handicap,
                    BfSide::BACK,
                    cbmlt.m_bfSelection.m_availableToBackPrice.front(),
                    takeSize);
    }
  }
  else // Lay
  {
    qDebug() << "Place pressed from row: " << QString::number(row);
    qDebug() << "mid" << cbmlt.m_bfMarket.m_marketId;
    qDebug() << "sid" << cbmlt.m_bfSelection.m_selectionId;
    qDebug() << "handicap" << cbmlt.m_bfSelection.m_handicap;
    qDebug() << "side" << BfSide::toStr(BfSide::LAY);
    if (cbmlt.m_bfSelection.m_availableToLayPrice.size() > 0 &&
        cbmlt.m_bfSelection.m_availableToLaySize.size())
    {
      qDebug() << "takePrice" << cbmlt.m_bfSelection.m_availableToLayPrice.front();
      double takeSize = cbmlt.m_simLaySize;
      if (cbmlt.m_bfSelection.m_availableToLaySize.front() < takeSize)
        takeSize = cbmlt.m_bfSelection.m_availableToLaySize.front();
      qDebug() << "takeSize" << takeSize;

      emit placeBet(cbmlt.m_bfMarket.m_marketId,
                    cbmlt.m_bfSelection.m_selectionId,
                    cbmlt.m_bfSelection.m_handicap,
                    BfSide::LAY,
                    cbmlt.m_bfSelection.m_availableToLayPrice.front(),
                    takeSize);
    }
  }
}

