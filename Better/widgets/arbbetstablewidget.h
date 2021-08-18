#ifndef ARBBETSTABLEWIDGET_H
#define ARBBETSTABLEWIDGET_H

#include <list>

#include <QWidget>
#include <QTableWidget>

#include "bftypes/bfplaceinstruction.h"
#include "types/bfarbbet.h"

using namespace BfLib;

class ArbBetsTableWidget : public QTableWidget
{
  Q_OBJECT

public:
  ArbBetsTableWidget(QWidget *parent = 0);

signals:
  void placeBet(QString,BfLib::BfPlaceInstruction);
  void onLuckyBetsChanged(bool);
public slots:
  void receivedArbBetsUpdate(std::list<BfArbBet>);
  void on_pushButtonPlace_clicked();
private:
  std::list<BfArbBet> m_arbBetsReceived;
  QString constructText(const BfArbBet &pi);

  bool m_hasLuckeyBets;
};

#endif // ARBBETSTABLEWIDGET_H
