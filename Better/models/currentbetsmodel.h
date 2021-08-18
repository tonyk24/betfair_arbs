#ifndef CURRENTBETSMODEL_H
#define CURRENTBETSMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QModelIndex>

#include "bftypes/bfmarket.h"
#include "bftypes/bfevent.h"
#include "types/extbet.h"
#include "extsites/extsitesp.h"
#include "extarbcalculator.h"

#include "models/currentbetsmodellisttype.h"

using namespace BfLib;


class CurrentBetsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CurrentBetsModel(QObject *parent, BfEvent bfEvent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setMarketData(std::list<BetfairMarket> m_marketData);
    void updateSPOdds(ExtSiteSPOdds odds);

    bool flipCheckState(const QModelIndex &index);
    bool flipExtCheckState(const QModelIndex &index);
    CurrentBetsModelListType getDataForRow(int row);
    void setMaxExposure(double maxExposure)
    {
      m_maxExposure = maxExposure;
    }

signals:
    void hasAribtrageBetsChanged(bool hasArbitrageBets);
public slots:

private:
    void checkForArbitrageExistance();
    bool m_hasArbitrageBets;

    BfEvent m_bfEvent;
    std::vector<CurrentBetsModelListType> m_data;
    double m_maxExposure;
};

#endif // CURRENTBETSMODEL_H
