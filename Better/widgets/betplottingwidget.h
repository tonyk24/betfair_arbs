#ifndef BETPLOTTINGWIDGET_H
#define BETPLOTTINGWIDGET_H

#include <list>
#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QMap>

#include "bftypes/bfmarket.h"
#include "..\qcustomplot\qcustomplot.h"

using namespace BfLib;

class BetPlottingWidget : public QWidget
{
  Q_OBJECT
public:
  BetPlottingWidget(QWidget *parent = 0);

signals:

public slots:
  void receivedMarketData(std::list<BfLib::BetfairMarket>);
  void comboSelectionChanged(QString);
  void plotButtonClicked(bool);
private:
  void updateGraph();
  QMap<QDateTime,std::list<BfLib::BetfairMarket> > m_marketData;
  QCustomPlot *m_customPlot;

  QComboBox *m_combobox1;
  QComboBox *m_combobox2;
  QComboBox *m_combobox3;
  QPushButton *m_pushButtonPlot;

  QString m_comboSelection1;
  QString m_comboSelection2;
  QString m_comboSelection3;
};

#endif // BETPLOTTINGWIDGET_H
