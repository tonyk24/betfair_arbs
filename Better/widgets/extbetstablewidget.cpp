#include <cmath>

#include <QDebug>
#include "widgets/extbetstablewidget.h"

ExtBetsTableWidget::ExtBetsTableWidget(QWidget *parent, BfEvent bfEvent) :
  QTableWidget(parent),
  m_bfEvent(bfEvent)
{
  // Initialize external bets table
  setRowCount(9);
  setColumnCount(8);
  QStringList m_TableHeader;
  m_TableHeader<<"Name" << "Type" << "Odds" << "Size" << "Simulate"
              << "Outcome1" << "Outcome2" << "Result";
  setHorizontalHeaderLabels(m_TableHeader);
  setColumnWidth(7, 400);

  QTableWidgetItem *simCheckBox1 = new QTableWidgetItem("back");
  setItem(0, 0, new QTableWidgetItem("Ext"));
  setItem(0, 1, new QTableWidgetItem("MO_Home"));
  setItem(0, 2, new QTableWidgetItem(""));
  setItem(0, 3, new QTableWidgetItem("30"));
  simCheckBox1->setCheckState(Qt::Unchecked);
  setItem(0, 4, simCheckBox1);
  setItem(0, 5, new QTableWidgetItem("0.0"));
  setItem(0, 6, new QTableWidgetItem("0.0"));
  setItem(0, 7, new QTableWidgetItem(""));

  QTableWidgetItem *simCheckBox3 = new QTableWidgetItem("back");
  setItem(1, 0, new QTableWidgetItem("Ext"));
  setItem(1, 1, new QTableWidgetItem("MO_Away"));
  setItem(1, 2, new QTableWidgetItem(""));
  setItem(1, 3, new QTableWidgetItem("30"));
  simCheckBox3->setCheckState(Qt::Unchecked);
  setItem(1, 4, simCheckBox3);
  setItem(1, 5, new QTableWidgetItem("0.0"));
  setItem(1, 6, new QTableWidgetItem("0.0"));
  setItem(1, 7, new QTableWidgetItem(""));

  QTableWidgetItem *simCheckBox2 = new QTableWidgetItem("back");
  setItem(2, 0, new QTableWidgetItem("Ext"));
  setItem(2, 1, new QTableWidgetItem("MO_Draw"));
  setItem(2, 2, new QTableWidgetItem(""));
  setItem(2, 3, new QTableWidgetItem("30"));
  simCheckBox2->setCheckState(Qt::Unchecked);
  setItem(2, 4, simCheckBox2);
  setItem(2, 5, new QTableWidgetItem("0.0"));
  setItem(2, 6, new QTableWidgetItem("0.0"));
  setItem(2, 7, new QTableWidgetItem(""));

  QTableWidgetItem *simCheckBox4 = new QTableWidgetItem("back");
  setItem(3, 0, new QTableWidgetItem("Ext"));
  setItem(3, 1, new QTableWidgetItem("OU_Over05"));
  setItem(3, 2, new QTableWidgetItem(""));
  setItem(3, 3, new QTableWidgetItem("30"));
  simCheckBox4->setCheckState(Qt::Unchecked);
  setItem(3, 4, simCheckBox4);
  setItem(3, 5, new QTableWidgetItem("0.0"));
  setItem(3, 6, new QTableWidgetItem("0.0"));
  setItem(3, 7, new QTableWidgetItem(""));

  QTableWidgetItem *simCheckBox5 = new QTableWidgetItem("back");
  setItem(4, 0, new QTableWidgetItem("Ext"));
  setItem(4, 1, new QTableWidgetItem("OU_Under05"));
  setItem(4, 2, new QTableWidgetItem(""));
  setItem(4, 3, new QTableWidgetItem("30"));
  simCheckBox5->setCheckState(Qt::Unchecked);
  setItem(4, 4, simCheckBox5);
  setItem(4, 5, new QTableWidgetItem("0.0"));
  setItem(4, 6, new QTableWidgetItem("0.0"));
  setItem(4, 7, new QTableWidgetItem(""));

  QTableWidgetItem *simCheckBox6 = new QTableWidgetItem("back");
  setItem(5, 0, new QTableWidgetItem("Ext"));
  setItem(5, 1, new QTableWidgetItem("OU_Over15"));
  setItem(5, 2, new QTableWidgetItem(""));
  setItem(5, 3, new QTableWidgetItem("30"));
  simCheckBox6->setCheckState(Qt::Unchecked);
  setItem(5, 4, simCheckBox6);
  setItem(5, 5, new QTableWidgetItem("0.0"));
  setItem(5, 6, new QTableWidgetItem("0.0"));
  setItem(5, 7, new QTableWidgetItem(""));

  QTableWidgetItem *simCheckBox7 = new QTableWidgetItem("back");
  setItem(6, 0, new QTableWidgetItem("Ext"));
  setItem(6, 1, new QTableWidgetItem("OU_Under15"));
  setItem(6, 2, new QTableWidgetItem(""));
  setItem(6, 3, new QTableWidgetItem("30"));
  simCheckBox7->setCheckState(Qt::Unchecked);
  setItem(6, 4, simCheckBox7);
  setItem(6, 5, new QTableWidgetItem("0.0"));
  setItem(6, 6, new QTableWidgetItem("0.0"));
  setItem(6, 7, new QTableWidgetItem(""));

  QTableWidgetItem *simCheckBox8 = new QTableWidgetItem("back");
  setItem(7, 0, new QTableWidgetItem("Ext"));
  setItem(7, 1, new QTableWidgetItem("OU_Over25"));
  setItem(7, 2, new QTableWidgetItem(""));
  setItem(7, 3, new QTableWidgetItem("30"));
  simCheckBox8->setCheckState(Qt::Unchecked);
  setItem(7, 4, simCheckBox8);
  setItem(7, 5, new QTableWidgetItem("0.0"));
  setItem(7, 6, new QTableWidgetItem("0.0"));
  setItem(7, 7, new QTableWidgetItem(""));

  QTableWidgetItem *simCheckBox9 = new QTableWidgetItem("back");
  setItem(8, 0, new QTableWidgetItem("Ext"));
  setItem(8, 1, new QTableWidgetItem("OU_Under25"));
  setItem(8, 2, new QTableWidgetItem(""));
  setItem(8, 3, new QTableWidgetItem("30"));
  simCheckBox9->setCheckState(Qt::Unchecked);
  setItem(8, 4, simCheckBox9);
  setItem(8, 5, new QTableWidgetItem("0.0"));
  setItem(8, 6, new QTableWidgetItem("0.0"));
  setItem(8, 7, new QTableWidgetItem(""));

  connect(this, SIGNAL(cellClicked(int, int)),
          this,SLOT(on_pushButtonSimulateExt_checked(int, int)));
  connect(this, SIGNAL(cellChanged(int,int)),
          this, SLOT(on_tableWidgetExt_cellChanged(int,int)));
}

void ExtBetsTableWidget::receivedExtArbBetsUpdate(std::list<ExtBet> extBets)
{
  std::list<ExtBet> greenExtBets;

  for (int row=0; row<rowCount(); row++)
  {
    for (std::list<ExtBet>::iterator it = extBets.begin();
         it != extBets.end(); it++)
    {
      //qDebug() << "-------------";
      //qDebug() << it->m_name;
      //qDebug() << item(row, 0)->text();
      //qDebug() << it->m_type;
      //qDebug() << ExtBet::toEnumType(item(row, 1)->text());
      if (it->m_name == item(row, 0)->text() &&
          it->m_type == ExtBet::toEnumType(item(row, 1)->text()))
      {
        setItem(row, 5, new QTableWidgetItem(QString::number(it->m_outCome1)));
        setItem(row, 6, new QTableWidgetItem(QString::number(it->m_outCome2)));
        if (it->m_outCome1 > 0.0 &&
            it->m_outCome2 > 0.0)
          greenExtBets.push_back(*it);
        setItem(row, 7, new QTableWidgetItem(it->m_arbResult));

        double bfPrice = 0.0;
        double bfSize = 0.0;
        bool foundBfPriceSize = findLayPriceSizeForExtBet(it->m_type, bfPrice, bfSize);
        bool hasOdds = false;
        double odds = item(row, 2)->text().toDouble(&hasOdds);

        //qDebug() << "foundBfPriceSize= " << foundBfPriceSize;
        //qDebug() << "bfPrice= " << bfPrice;
        //qDebug() << "bfSize= " << bfSize;
        //qDebug() << "hasOdds= " << hasOdds;
        //qDebug() << "odds= " << odds;
        if (foundBfPriceSize && hasOdds)
        {
          //          qDebug() << "extType" << it->m_type;
          //          qDebug() << "tableType" << item(row, 1)->text();
          //          qDebug() << "bfPrice= " << bfPrice;
          //          qDebug() << "bfSize= " << bfSize;
          //          qDebug() << "odds= " << odds;
          double size = (bfPrice*bfSize) / odds;
          //qDebug() << "size= " << size;
          //qDebug() << "ExtSize= " << size;
          size = round( size * 10.0 ) / 10.0;
          setItem(row, 3,
                  new QTableWidgetItem(QString::number(size)));
        }
      }
    }
  }

  emit extBetsGreenUpdated(greenExtBets);
}

void ExtBetsTableWidget::receivedBfPriceSimLaySize( std::list<BfPriceSimLaySize> bflayPriceSimSize)
{
  m_bflayPriceSimSize = bflayPriceSimSize;
}

void ExtBetsTableWidget::on_tableWidgetExt_cellChanged(int row, int column)
{
  Q_UNUSED(row)

  if (column == 2)
  {
    std::list<ExtBet> extBets;
    for (int row = 0; row < rowCount(); row++)
    {
      if (item(row, 2) == 0)
        continue;
      bool isNumber = false;
      item(row, 2)->text().toDouble(&isNumber);
      if(isNumber)
      {
        ExtBet extBet(item(row, 0)->text(),
                      ExtBet::toEnumType(item(row, 1)->text()),
                      item(row, 2)->text().toDouble(),
                      item(row, 3)->text().toDouble(),
                      true,
                      item(row, 5)->text().toDouble(),
                      item(row, 6)->text().toDouble(),
                      item(row, 7)->text());
        extBets.push_back(extBet);

      }
    }
    emit extBetsUpdated(extBets);
  }
}

void ExtBetsTableWidget::on_pushButtonSimulateExt_checked(int row, int column)
{
  qDebug() << "on_pushButtonSimulateExt_checked";
  if (column == 4)
  {
    qDebug() << QString::number(column);
    if (item(row, 4)->checkState() == Qt::Checked)
    {
      if (item(row, 2) == 0)
        return;
      bool isNumber = false;
      item(row, 2)->text().toDouble(&isNumber);
      if(isNumber)
      {
        //qDebug() << "name= " << item(row, 0)->text();
        //qDebug() << "type= " << item(row, 1)->text();
        ExtBet extBet(item(row, 0)->text(),
                      ExtBet::toEnumType(item(row, 1)->text()),
                      item(row, 2)->text().toDouble(),
                      item(row, 3)->text().toDouble(),
                      true,
                      item(row, 5)->text().toDouble(),
                      item(row, 6)->text().toDouble(),
                      item(row, 7)->text());
        // Add simulate bet
        emit placeExtBetSimulated(extBet);
      }

    }
    else
    {
      // Remove simulate bet
      if (item(row, 2) == 0)
        return;
      bool isNumber = false;
      item(row, 2)->text().toDouble(&isNumber);
      if(isNumber)
      {
        emit placeExtBetSimulatedRemoved(ExtBet(item(row, 0)->text(),
                                                ExtBet::toEnumType(item(row, 1)->text()),
                                                item(row, 2)->text().toDouble(),
                                                item(row, 3)->text().toDouble(),
                                                true,
                                                item(row, 5)->text().toDouble(),
                                                item(row, 6)->text().toDouble(),
                                                item(row, 7)->text()));
      }
    }
  }
}

void ExtBetsTableWidget::updateSPOdds(ExtSiteSPOdds odds)
{
  setItem(0, 2, new QTableWidgetItem(QString::number(odds.m_homeOdds)));
  setItem(1, 2, new QTableWidgetItem(QString::number(odds.m_awayOdds)));
  setItem(2, 2, new QTableWidgetItem(QString::number(odds.m_drawOdds)));
}

bool ExtBetsTableWidget::findLayPriceSizeForExtBet(ExtBet::EnumType type,
                                                   double &bfPrice,
                                                   double &bfSize)
{
  QStringList sl = m_bfEvent.m_name.split(" v ");
  QString homeTeamName = sl.at(0);
  QString awayTeamName = sl.at(1);

  for (std::list<BfPriceSimLaySize>::iterator it = m_bflayPriceSimSize.begin();
       it != m_bflayPriceSimSize.end(); it++)
  {

    if ((it->m_SelectionName == homeTeamName && type == ExtBet::MO_Home) ||
        (it->m_SelectionName == awayTeamName && type == ExtBet::MO_Away) ||
        (it->m_SelectionName == "The Draw" && type == ExtBet::MO_Draw) ||
        (it->m_SelectionName == "Over 0.5 Goals" && type == ExtBet::OU_Over05) ||
        (it->m_SelectionName == "Under 0.5 Goals" && type == ExtBet::OU_Under05) ||
        (it->m_SelectionName == "Over 1.5 Goals" && type == ExtBet::OU_Over15) ||
        (it->m_SelectionName == "Under 1.5 Goals" && type == ExtBet::OU_Under15) ||
        (it->m_SelectionName == "Over 2.5 Goals" && type == ExtBet::OU_Over25) ||
        (it->m_SelectionName == "Under 2.5 Goals" && type == ExtBet::OU_Under25))

    {
      // BfPrice
      bfPrice = it->m_bfPrice;
      // BfSimLaySize
      bfSize = it->m_bfSimLaySize;
      return true;
    }
  }
  return false;
}
