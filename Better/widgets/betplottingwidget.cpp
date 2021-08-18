#include <cmath>

#include <QString>
#include <QVector>
#include <QComboBox>

#include "bftypes/bfselection.h"

#include "betplottingwidget.h"

BetPlottingWidget::BetPlottingWidget(QWidget *parent):
  QWidget(parent),
  m_customPlot(new QCustomPlot(this)),
  m_combobox1(new QComboBox(this)),
  m_combobox2(new QComboBox(this)),
  m_combobox3(new QComboBox(this)),
  m_pushButtonPlot(new QPushButton(this))
{

  connect(m_combobox1, SIGNAL(currentTextChanged(QString)),
          this, SLOT(comboSelectionChanged(QString)));
  connect(m_combobox2, SIGNAL(currentTextChanged(QString)),
          this, SLOT(comboSelectionChanged(QString)));
  connect(m_combobox3, SIGNAL(currentTextChanged(QString)),
          this, SLOT(comboSelectionChanged(QString)));
  connect(m_pushButtonPlot, SIGNAL(clicked(bool)),
          this, SLOT(plotButtonClicked(bool)));

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(m_combobox1,0,0,1,1);
  layout->addWidget(m_combobox2,0,1,1,1);
  layout->addWidget(m_combobox3,0,2,1,1);
  layout->addWidget(m_pushButtonPlot,0,3,1,1);
  layout->addWidget(m_customPlot,1,0,5,5);

  setLayout(layout);

  //m_customPlot->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
}

void BetPlottingWidget::receivedMarketData(std::list<BfLib::BetfairMarket> marketData)
{
  m_marketData.insert(QDateTime::currentDateTime(), marketData);

  for (std::list<BfLib::BetfairMarket>::const_iterator itMarket = marketData.begin();
       itMarket != marketData.end(); itMarket++)
  {

    for (std::list<BetfairSelection>::const_iterator itSel = itMarket->m_selections.begin();
         itSel != itMarket->m_selections.end(); itSel++)
    {
      QString item = itMarket->m_marketName + " :: " +
          itSel->m_selectionName + " :: " +
          "Back";
      int index = m_combobox1->findData(item);
      if (index == -1)
        m_combobox1->addItem(item);

      item = itMarket->m_marketName + " :: " +
          itSel->m_selectionName + " :: " +
          "Lay";
      index = m_combobox1->findData(item);
      if (index == -1)
        m_combobox1->addItem(item);

      item =       itMarket->m_marketName + " :: " +
          itSel->m_selectionName + " :: " +
          "Back";
      index = m_combobox2->findData(item);
      if (index == -1)
        m_combobox2->addItem(item);

      item = itMarket->m_marketName + " :: " +
          itSel->m_selectionName + " :: " +
          "Lay";
      index = m_combobox2->findData(item);
      if (index == -1)
        m_combobox2->addItem(item);

      item = itMarket->m_marketName + " :: " +
          itSel->m_selectionName + " :: " +
          "Back";
      index = m_combobox3->findData(item);
      if (index == -1)
        m_combobox3->addItem(item);

      item = itMarket->m_marketName + " :: " +
          itSel->m_selectionName + " :: " +
          "Lay";
      index = m_combobox3->findData(item);
      if (index == -1)
        m_combobox3->addItem(item);

    }
  }

  int index = m_combobox1->findData(m_comboSelection1);
  if ( index != -1 ) { // -1 for not found
    m_combobox1->setCurrentIndex(index);
  }
  index = m_combobox2->findData(m_comboSelection2);
  if ( index != -1 ) { // -1 for not found
    m_combobox2->setCurrentIndex(index);
  }
  index = m_combobox3->findData(m_comboSelection3);
  if ( index != -1 ) { // -1 for not found
    m_combobox3->setCurrentIndex(index);
  }
}

void BetPlottingWidget::comboSelectionChanged(QString val)
{
  //qDebug() << val;
  if (sender() == m_combobox1)
    m_comboSelection1 = m_combobox1->currentText();
  if (sender() == m_combobox2)
    m_comboSelection2 = m_combobox2->currentText();
  if (sender() == m_combobox3)
    m_comboSelection3 = m_combobox3->currentText();
}

void BetPlottingWidget::plotButtonClicked(bool)
{
updateGraph();
}

void BetPlottingWidget::updateGraph()
{
  if (m_comboSelection1 != "")
  {
    if (m_marketData.size() == 0)
      return;
    // generate some data:
    QStringList stringList1 = m_comboSelection1.split(" :: ");
    QVector<double> x1, y1; // initialize with entries 0..100
    double firstMs = m_marketData.keys().first().toMSecsSinceEpoch();
    double xMin1 = 0.0;
    double xMax1 = 0.0;
    double yMin1 = 0.0;
    double yMax1 = 0.0;
    QMapIterator<QDateTime,std::list<BfLib::BetfairMarket> > it(m_marketData);
    while (it.hasNext()) {
      it.next();
      double valX1 = (it.key().toMSecsSinceEpoch() -
                     firstMs)/1000.0;
      if (valX1 > xMax1)
        xMax1 = valX1;
      x1.push_back(valX1);

      for (std::list<BfLib::BetfairMarket>::const_iterator itMarket = it.value().begin();
           itMarket != it.value().end(); itMarket++)
      {

        for (std::list<BetfairSelection>::const_iterator itSel = itMarket->m_selections.begin();
             itSel != itMarket->m_selections.end(); itSel++)
        {
          if (itMarket->m_marketName == stringList1.at(0) &&
              itSel->m_selectionName == stringList1.at(1))
          {
            if (stringList1.at(2) == "Back")
            {
              double val = 0.0;
              if (itSel->m_availableToBackPrice.size() > 0)
                val = itSel->m_availableToBackPrice.front();

              if (val > yMax1)
                yMax1 = val;

              y1.push_back(val);
            }
            else
            {
              double val = 0.0;
              if (itSel->m_availableToLayPrice.size() > 0)
                val = itSel->m_availableToLayPrice.front();

              if (val > yMax1)
                yMax1 = val;

              y1.push_back(val);
            }
          }
        }
      }
    }
    // generate some data:
    QStringList stringList2 = m_comboSelection2.split(" :: ");
    QVector<double> x2, y2; // initialize with entries 0..100
    double xMin2 = 0.0;
    double xMax2 = 0.0;
    double yMin2 = 0.0;
    double yMax2 = 0.0;
    QMapIterator<QDateTime,std::list<BfLib::BetfairMarket> > it2(m_marketData);
    while (it2.hasNext()) {
      it2.next();
      double valX2 = (it2.key().toMSecsSinceEpoch() -
                     firstMs)/1000.0;
      if (valX2 > xMax2)
        xMax2 = valX2;
      x2.push_back(valX2);

      for (std::list<BfLib::BetfairMarket>::const_iterator itMarket = it2.value().begin();
           itMarket != it2.value().end(); itMarket++)
      {

        for (std::list<BetfairSelection>::const_iterator itSel = itMarket->m_selections.begin();
             itSel != itMarket->m_selections.end(); itSel++)
        {
          if (itMarket->m_marketName == stringList2.at(0) &&
              itSel->m_selectionName == stringList2.at(1))
          {
            if (stringList2.at(2) == "Back")
            {
              double val = 0.0;
              if (itSel->m_availableToBackPrice.size() > 0)
                val = itSel->m_availableToBackPrice.front();

              if (val > yMax2)
                yMax2 = val;

              y2.push_back(val);
            }
            else
            {
              double val = 0.0;
              if (itSel->m_availableToLayPrice.size() > 0)
                val = itSel->m_availableToLayPrice.front();

              if (val > yMax2)
                yMax1 = val;

              y2.push_back(val);
            }
          }
        }
      }
    }
    // generate some data:
    QStringList stringList3 = m_comboSelection3.split(" :: ");
    QVector<double> x3, y3; // initialize with entries 0..100
    double xMin3 = 0.0;
    double xMax3 = 0.0;
    double yMin3 = 0.0;
    double yMax3 = 0.0;
    QMapIterator<QDateTime,std::list<BfLib::BetfairMarket> > it3(m_marketData);
    while (it3.hasNext()) {
      it3.next();
      double valX3 = (it3.key().toMSecsSinceEpoch() -
                     firstMs)/1000.0;
      if (valX3 > xMax3)
        xMax3 = valX3;
      x3.push_back(valX3);

      for (std::list<BfLib::BetfairMarket>::const_iterator itMarket = it.value().begin();
           itMarket != it.value().end(); itMarket++)
      {

        for (std::list<BetfairSelection>::const_iterator itSel = itMarket->m_selections.begin();
             itSel != itMarket->m_selections.end(); itSel++)
        {
          if (itMarket->m_marketName == stringList3.at(0) &&
              itSel->m_selectionName == stringList3.at(1))
          {
            if (stringList3.at(2) == "Back")
            {
              double val = 0.0;
              if (itSel->m_availableToBackPrice.size() > 0)
                val = itSel->m_availableToBackPrice.front();

              if (val > yMax3)
                yMax3 = val;

              y3.push_back(val);
            }
            else
            {
              double val = 0.0;
              if (itSel->m_availableToLayPrice.size() > 0)
                val = itSel->m_availableToLayPrice.front();

              if (val > yMax3)
                yMax3 = val;

              y3.push_back(val);
            }
          }
        }
      }
    }
    // create graph and assign data to it:
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setData(x1, y1);
    m_customPlot->graph(0)->setPen(QPen(Qt::blue));

    m_customPlot->addGraph();
    m_customPlot->graph(1)->setData(x2, y2);
    m_customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

    m_customPlot->addGraph();
    m_customPlot->graph(2)->setData(x3, y3);
    m_customPlot->graph(2)->setPen(QPen(Qt::green)); // line color red for second graph

    // give the axes some labels:
    m_customPlot->xAxis->setLabel("Time (s)");
    m_customPlot->yAxis->setLabel("Odds");
    // set axes ranges, so we see all data:
    m_customPlot->xAxis->setRange(xMin1, std::max(std::max(xMax1,xMax2),xMax3));
    m_customPlot->yAxis->setRange(yMin1, std::max(std::max(yMax1, yMax2), yMax3));
    m_customPlot->replot();
  }
}

