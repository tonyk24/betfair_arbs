#ifndef BFBETSTABLEWIDGET_H
#define BFBETSTABLEWIDGET_H

#include <QTableView>
#include <QObject>
#include <QString>
#include <QHash>
#include <QSignalMapper>

#include "bfenums/bfside.h"

#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"

#include "types/bfpricesimlaysize.h"
#include "types/extbet.h"

#include "models/currentbetsmodel.h"

#include "extarbcalculator.h"

using namespace BfLib;

class BfBetsTableView : public QTableView
{
  Q_OBJECT

public:
  BfBetsTableView(QWidget *parent, BfEvent bfEvent);

  void updateMaxExposure(double maxExposure);
signals:
  void bfPriceSimLaySizeUpdated(std::list<BfPriceSimLaySize> BflayPriceSimSize);

  void placeBet(QString marketId, qint64 selectionId,
                double handicap, BfLib::BfSide::Enum side,
                double takePrice, double takeSize);
  void placeBetSimulated(QString marketId, qint64 selectionId,
                         double handicap, BfLib::BfSide::Enum side,
                         double takePrice, double takeSize);
  void placeBetSimulatedRemove(QString marketId, qint64 selectionId,
                               double handicap, BfLib::BfSide::Enum side);
  void placeExtBetSimulated(ExtBet);
  void placeExtBetSimulatedRemoved(ExtBet);
  void hasAribtrageBetsChanged(bool hasArbitrageBets);
public slots:
  void receivedMarketData( std::list<BfLib::BetfairMarket> marketBook);
  void updateSPOdds(ExtSiteSPOdds odds);
  void receivedAribtrageBetsChanged(bool);

  void on_pushButtonSimulate_checked(QModelIndex);
  void on_pushButtonPlace_clicked(int row);

private:
  //void colorRows();
  BfEvent m_bfEvent;
  double m_maxExposure;
  CurrentBetsModel *m_model;


  QSignalMapper *m_signalMapper;

  ExtArbCalculator m_extArbCalculator;


  // String = MarketId, SelectionId, handicap, side
  QString constructSimHashKey(QString marketId,
                              qint64 selId,
                              double handicap,
                              BfSide::Enum side)
  {
    return marketId +
        QString::number(selId) +
        QString::number(handicap) +
        BfSide::toStr(side);
  }

  QHash<QString,bool> m_bfBetSimulatedHash;
};

#endif // BFBETSTABLEWIDGET_H
