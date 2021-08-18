#ifndef BfEventMARKETSMAP_H
#define BfEventMARKETSMAP_H

#include <map>
#include <list>
#include <vector>
#include <utility>
#include <map>
#include <list>

#include <QString>
#include <QTextStream>

#include "bftypes/bfmarket.h"
#include "bftypes/bfevent.h"
#include "bfenums/bfcompetition.h"

using namespace BfLib;

/*
 * A number of groups
 * 200 points per group
 * */
class MarketsData {
public:
  MarketsData(int groups);
  ~MarketsData();

  bool isEventAdded(QString eventId);
  void removeEvent(QString eventId);
  std::list<QString> getActiveEvents();

  void increaseUpdateSlot();
  void getMarketIdsToUpdate(std::list<QString> &marketIdsToUpdate);

  bool addEvent(const BfEvent &event,
                const std::list<BetfairMarket> &markets);
  std::list< std::pair<BfEvent, std::list<BetfairMarket> > > * updateMarketBook(const std::list<BetfairMarket> &markets);

  void mergeNewSelections(std::list<BetfairMarket>::iterator itExistingMarket,
                          std::list<BetfairMarket>::const_iterator itNewMarket);

  QString getActiveEventsStr() {
    QString out;
    QTextStream tsOut(&out);
    for (std::size_t i=0; i<m_activeEventMarketsData.size(); i++) {
      for (std::list<std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[i].begin();
           it != m_activeEventMarketsData[i].end(); it++) {
        tsOut << "{ [" << QString::number(i) << "] " << it->first.m_eventId << " -- ";
        tsOut << it->first.m_name << "\n  ";
        tsOut << it->first.m_countryCode << " -- ";
        tsOut << it->first.m_openDate.toString() << "\n  ";
        tsOut << BfCompetition::toStr(it->first.m_competition) << "}\n";
      }
    }

    return out;
  }

  QString getActiveEventsDetailsStr(std::size_t slot) {
    QString out;
    QTextStream tsOut(&out);
    if (slot < m_activeEventMarketsData.size()) {
      for (std::list<std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[slot].begin();
           it != m_activeEventMarketsData[slot].end(); it++) {
        tsOut << "{ [" << QString::number(slot) << "] " << it->first.m_eventId << " -- ";
        tsOut << it->first.m_name << "\n  ";
        tsOut << BfCompetition::toStr(it->first.m_competition) << "}\n";
        for (std::list<BetfairMarket>::iterator itM = it->second.begin();
             itM != it->second.end(); itM++) {
          tsOut << " * " << itM->m_marketName << " - " << itM->m_marketId << "\n";
          tsOut << "   " << BfMarketStatus::toStr(itM->m_marketStatus) << " - " << QString::number(itM->m_totalMatched) << "\n";
        }
      }
    }
    else {
      tsOut << "Invalid slot..";
    }

    return out;
  }

  QString getActiveEventBetsStr(std::size_t slot, std::size_t index) {
    QString out;
    QTextStream tsOut(&out);
    if (slot < m_activeEventMarketsData.size()) {
      std::size_t counter = 0;
      for (std::list<std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[slot].begin();
           it != m_activeEventMarketsData[slot].end(); it++, counter++) {
        if ( counter == index) {
          tsOut << "{ [" << QString::number(slot) << "," << QString::number(index) << "] " << it->first.m_eventId << " -- ";
          tsOut << it->first.m_name << "\n  ";
          tsOut << BfCompetition::toStr(it->first.m_competition) << "}\n";
          for (std::list<BetfairMarket>::iterator itM = it->second.begin();
               itM != it->second.end(); itM++) {
            tsOut << " * " << itM->m_marketName << " - " << itM->m_marketId << " - " << BfMarketStatus::toStr(itM->m_marketStatus) << ", eID= " << it->first.m_eventId <<"\n";
            for (std::list<BetfairSelection>::const_iterator itSel = itM->m_selections.begin();
                 itSel != itM->m_selections.end(); itSel++) {
              tsOut << "     " << QString::number(itSel->m_selectionId) << " " << itSel->m_selectionName << " " << itSel->m_status << " hand= " << QString::number(itSel->m_handicap)
                    << "\n     Back= ";
              if (itSel->m_availableToBackPrice.size() > 0 && itSel->m_availableToBackSize.size() > 0) {
                tsOut << QString::number(itSel->m_availableToBackPrice[0]) << "(" << itSel->m_availableToBackSize[0] << ")";
              } else {
                tsOut << "NA";
              }
              tsOut << " Lay=";
              if (itSel->m_availableToLayPrice.size() > 0 && itSel->m_availableToLaySize.size() > 0) {
                tsOut << QString::number(itSel->m_availableToLayPrice[0]) << "(" << itSel->m_availableToLaySize[0] << ")\n";
              } else {
                tsOut << "NA\n";
              }
            }
          }
          return out;
        }
      }
    }
    else {
      tsOut << "Invalid slot..";
    }

    return "Invalid index..";
  }

  QString getActiveEventBetsMarketStr(std::size_t slot, std::size_t index, QString marketName) {
    QString out;
    QTextStream tsOut(&out);
    if (slot < m_activeEventMarketsData.size()) {
      std::size_t counter = 0;
      for (std::list<std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[slot].begin();
           it != m_activeEventMarketsData[slot].end(); it++, counter++) {
        if ( counter == index) {
          tsOut << "{ [" << QString::number(slot) << "] " << it->first.m_eventId << " -- ";
          tsOut << it->first.m_name << "\n  ";
          tsOut << BfCompetition::toStr(it->first.m_competition) << "}\n";
          for (std::list<BetfairMarket>::iterator itM = it->second.begin();
               itM != it->second.end(); itM++) {
            if (itM->m_marketName == marketName) {
              tsOut << " * " << itM->m_marketName << " - " << itM->m_marketId << " - " << BfMarketStatus::toStr(itM->m_marketStatus) << "\n";
              for (std::list<BetfairSelection>::const_iterator itSel = itM->m_selections.begin();
                   itSel != itM->m_selections.end(); itSel++) {
                tsOut << "     " << QString::number(itSel->m_selectionId) << " " << itSel->m_selectionName << " " << itSel->m_status << " hand=" << QString::number(itSel->m_handicap)
                      << "\n     Back= ";
                if (itSel->m_availableToBackPrice.size() > 0 && itSel->m_availableToBackSize.size() > 0) {
                  tsOut << QString::number(itSel->m_availableToBackPrice[0]) << "(" << itSel->m_availableToBackSize[0] << ")";
                } else {
                  tsOut << "NA";
                }
                tsOut << " Lay=";
                if (itSel->m_availableToLayPrice.size() > 0 && itSel->m_availableToLaySize.size() > 0) {
                  tsOut << QString::number(itSel->m_availableToLayPrice[0]) << "(" << itSel->m_availableToLaySize[0] << ")\n";
                } else {
                  tsOut << "NA\n";
                }
              }
            }
          }
          return out;
        }
      }
    }
    else {
      tsOut << "Invalid slot..";
    }

    return "Invalid index..";
  }

private:
  bool belowMarketDataRequestLimit(int currentSlot, int numberOfNewMarkets);

  std::vector<std::list<std::pair<BfEvent, std::list<BetfairMarket> > > > m_activeEventMarketsData;

  // 0-indexed
  int m_marketDataUpdateSlot;
  const int m_marketDataUpdateGroupCount;

};

#endif // BfEventMARKETSMAP_H

