#ifndef EXTBETSTABLEWIDGET_H
#define EXTBETSTABLEWIDGET_H

#include <list>

#include <QTableWidget>
#include <QObject>
#include <QString>

#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"

#include "types/bfpricesimlaysize.h"
#include "types/extbet.h"

#include "extsites/extsitesp.h"


class ExtBetsTableWidget : public QTableWidget
{
  Q_OBJECT

public:
  ExtBetsTableWidget(QWidget *parent, BfEvent bfEvent);


signals:
  void extBetsUpdated(std::list<ExtBet>);
  void extBetsGreenUpdated(std::list<ExtBet>);
  void placeExtBetSimulated(ExtBet);
  void placeExtBetSimulatedRemoved(ExtBet);
public slots:
  void receivedExtArbBetsUpdate(std::list<ExtBet> extBets);
  void receivedBfPriceSimLaySize( std::list<BfPriceSimLaySize> BflayPriceSimSize);
  void on_tableWidgetExt_cellChanged(int row, int column);
  void on_pushButtonSimulateExt_checked(int row, int column);

  void updateSPOdds(ExtSiteSPOdds odds);
private:
  bool findLayPriceSizeForExtBet(ExtBet::EnumType type, double &bfPrice,
                                 double &bfSize);

  BfEvent m_bfEvent;
  std::list<BetfairMarket> m_marketBook;


  std::list<BfPriceSimLaySize> m_bflayPriceSimSize;
};

#endif // EXTBETSTABLEWIDGET_H
