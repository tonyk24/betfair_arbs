#include "arbbetstablewidget.h"

#include <QDebug>
#include <QPushButton>

ArbBetsTableWidget::ArbBetsTableWidget(QWidget *parent)
{
  setColumnCount(5);
  QStringList tableHeadertableWidget;
  tableHeadertableWidget<< "Id" << "MarketName" << "Sel. Name" << "Text" << "Place";
  setHorizontalHeaderLabels(tableHeadertableWidget);

  setColumnWidth(0, 40);
  setColumnWidth(1, 200);
  setColumnWidth(2, 200);
  setColumnWidth(3, 300);
  setColumnWidth(4, 60);

}

void ArbBetsTableWidget::receivedArbBetsUpdate(std::list<BfArbBet> arbBetsReceived)
{
  m_arbBetsReceived = arbBetsReceived;
  setRowCount(arbBetsReceived.size());
  int row = 0;

  for (std::list<BfArbBet>::iterator itArb = arbBetsReceived.begin();
       itArb != arbBetsReceived.end(); itArb++, row++)
  {
      setItem(row, 0, new QTableWidgetItem(QString::number(itArb->m_arbBetId)));
      setItem(row, 1, new QTableWidgetItem(itArb->m_market.m_marketName));
      setItem(row, 2, new QTableWidgetItem(itArb->m_selection.m_selectionName));
      setItem(row, 3, new QTableWidgetItem(constructText(*itArb)));

      // Add Place back button
      QPushButton* buttonPlace = new QPushButton();
      buttonPlace->setText("Back");
      connect(buttonPlace, SIGNAL(clicked()),this,SLOT(on_pushButtonPlace_clicked()));
      setCellWidget(row, 4, buttonPlace);
  }

  bool hasLuckyeBets = arbBetsReceived.size() > 0;
  if (hasLuckyeBets != m_hasLuckeyBets)
    emit onLuckyBetsChanged(hasLuckyeBets);
  m_hasLuckeyBets = hasLuckyeBets;
}

void ArbBetsTableWidget::on_pushButtonPlace_clicked()
{
  for(int row=0; row<rowCount(); row++)
  {
    if(sender() == cellWidget(row,4))
    {
      for (std::list<BfArbBet>::iterator itArb = m_arbBetsReceived.begin();
           itArb != m_arbBetsReceived.end(); itArb++)
      {
          if (QString::number(itArb->m_arbBetId) == item(row, 0)->text() &&
              item(row, 3)->text() == constructText(*itArb))
          {
            emit placeBet(itArb->m_market.m_marketId,itArb->m_pi);
          }
        }
    }
  }
}

QString ArbBetsTableWidget::constructText(const BfArbBet &arbBet)
{
  QString arbbet = QString::number(arbBet.m_pi.m_selectionId) + "_s"
      + BfSide::toStr(arbBet.m_pi.m_side) + "_p"
      + QString::number(arbBet.m_pi.m_limitOrder.m_price) + "_s"
      + QString::number(arbBet.m_pi.m_limitOrder.m_size);

  return arbbet;
}
