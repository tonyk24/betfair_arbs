#include <QDebug>

#include "betting/marketsdata.h"

#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"

MarketsData::MarketsData(int groups) :
  m_marketDataUpdateSlot(0),
  m_marketDataUpdateGroupCount(groups) {
  qDebug() << "MarketsData()";
  for (int i=0; i<m_marketDataUpdateGroupCount; i++) {
    m_activeEventMarketsData.push_back(std::list< std::pair<BfEvent, std::list<BetfairMarket> > >());
  }
}

MarketsData::~MarketsData() {
}

bool MarketsData::isEventAdded(QString eventId) {
  for (std::size_t i=0; i<m_activeEventMarketsData.size(); i++) {
    for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[i].begin();
         it != m_activeEventMarketsData[i].end(); it++) {
      if (it->first.m_eventId == eventId) {
        return true;
      }
    }
  }
  return false;
}


void MarketsData::removeEvent(QString eventId) {
  for (std::size_t i=0; i<m_activeEventMarketsData.size(); i++) {
    for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[i].begin();
         it != m_activeEventMarketsData[i].end(); it++) {
      if (it->first.m_eventId == eventId) {
        m_activeEventMarketsData[i].erase(it);
        return;
      }
    }
  }
}

std::list<QString> MarketsData::getActiveEvents() {
  std::list<QString> events;
  for (std::size_t i=0; i<m_activeEventMarketsData.size(); i++) {
    for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[i].begin();
         it != m_activeEventMarketsData[i].end(); it++) {
      events.push_back(it->first.m_eventId);
    }
  }
  return events;
}

void MarketsData::increaseUpdateSlot() {
  m_marketDataUpdateSlot = (m_marketDataUpdateSlot+1) % m_marketDataUpdateGroupCount;
}

void MarketsData::getMarketIdsToUpdate(std::list<QString> &marketIdsToUpdate) {
  for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[m_marketDataUpdateSlot].begin();
       it != m_activeEventMarketsData[m_marketDataUpdateSlot].end(); it++) {
    for (std::list<BetfairMarket>::iterator itMarket = it->second.begin();
         itMarket != it->second.end(); itMarket++) {
      marketIdsToUpdate.push_back(itMarket->m_marketId);
    }
  }
}

bool MarketsData::addEvent(const BfEvent &event,
                           const std::list<BetfairMarket> &markets) {
  //qDebug() << "MarketsData::addEvent, slots=" << QString::number(m_activeEventMarketsData.size());
  for (std::size_t i=0; i<m_activeEventMarketsData.size(); i++) {
    // Check if marketRequest limit is below with new markets added
    if (belowMarketDataRequestLimit(i, markets.size())) {
      qDebug() << "Adding event= " << event.m_eventId << ", to slot: " << QString::number(i);
      m_activeEventMarketsData[i].push_back(std::make_pair(event, markets));
      //qDebug() << "m_activeEventMarketsData[i].size()=" << QString::number(m_activeEventMarketsData[i].size());
      return true;
    }
  }
  return false;
}

std::list< std::pair<BfEvent, std::list<BetfairMarket> > > * MarketsData::updateMarketBook(const std::list<BetfairMarket> &marketsData) {
  if (marketsData.size() == 0) {
    return 0;
  }
  std::list<int> currentSlotList;
  // Find the slot for the received data
  for (std::size_t i=0; i<m_activeEventMarketsData.size(); i++) {
    for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator it = m_activeEventMarketsData[i].begin();
         it != m_activeEventMarketsData[i].end(); it++) {
      for (std::list<BetfairMarket>::iterator itMarket = it->second.begin();
           itMarket != it->second.end(); itMarket++) {

        // Loop received markets
        for(std::list<BetfairMarket>::const_iterator itRecMarket = marketsData.begin();
            itRecMarket != marketsData.end(); itRecMarket++) {
          if (itMarket->m_marketId == itRecMarket->m_marketId) {
            currentSlotList.push_back(i);
            //qDebug() << "currentSlotList.size()=" << QString::number(currentSlotList.size());
          }
        }
      }
    }
  }

  currentSlotList.sort();
  currentSlotList.unique();

  if (currentSlotList.size() == 0) {
    qWarning() << "MarketsData::updateMarketBook: Expecting non-existing slot for data";
    return 0;
  } else if (currentSlotList.size() > 1) {
    qWarning() << "MarketsData::updateMarketBook: Expecting unique slot for data";
    return 0;
  }

  int currentSlot = currentSlotList.front();

  // Reset data for slot
  for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator mapIt = m_activeEventMarketsData[currentSlot].begin();
       mapIt != m_activeEventMarketsData[currentSlot].end(); mapIt++) {
    for (std::list<BetfairMarket>::iterator itMarket = mapIt->second.begin();
         itMarket != mapIt->second.end(); itMarket++) {
      itMarket->m_totalMatched = 0.0;
      for (std::list<BetfairSelection>::iterator selIt = itMarket->m_selections.begin();
           selIt != itMarket->m_selections.end(); selIt++) {
        selIt->resetData();
      }
    }
  }

  // Update data for slot
  for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator mapIt = m_activeEventMarketsData[currentSlot].begin();
       mapIt != m_activeEventMarketsData[currentSlot].end(); mapIt++) {
    // Loop received markets
    for(std::list<BetfairMarket>::const_iterator itRecMarket = marketsData.begin();
        itRecMarket != marketsData.end(); itRecMarket++) {

      // Update selection and market data
      for (std::list<BetfairMarket>::iterator itMarket = mapIt->second.begin();
           itMarket != mapIt->second.end(); itMarket++) {
        if (itRecMarket->m_marketId == itMarket->m_marketId) {
          //qDebug() << "event: Competioon=" << mapIt->first.m_competition
          //         << ", str= " << BfCompetition::toStr(mapIt->first.m_competition);
          // Update competition data if unkown for event
          if ((mapIt->first.m_competition == BfCompetition::ALL ||
               mapIt->first.m_competition == BfCompetition::UNKOWN) &&
              itRecMarket->m_competition != BfCompetition::UNKOWN &&
              itRecMarket->m_competition != BfCompetition::ALL) {
            mapIt->first.m_competition = itRecMarket->m_competition;
          }
          //qDebug() << "event: Competioon=" << mapIt->first.m_competition
          //         << ", str= " << BfCompetition::toStr(mapIt->first.m_competition);
          itMarket->m_totalMatched = itRecMarket->m_totalMatched;
          itMarket->m_marketStatus = itRecMarket->m_marketStatus;
          mergeNewSelections(itMarket, itRecMarket);
        }
      }

      // Possibly add new market if we don't exceed 200 points for this slot
    }
  }
  return &m_activeEventMarketsData[currentSlot];
}

void MarketsData::mergeNewSelections(std::list<BetfairMarket>::iterator itExistingMarket,
                                     std::list<BetfairMarket>::const_iterator itNewMarket) {
  for (std::list<BetfairSelection>::const_iterator itNewSelection = itNewMarket->m_selections.begin();
       itNewSelection != itNewMarket->m_selections.end(); itNewSelection++) {
    bool foundNewSelection = false;
    for (std::list<BetfairSelection>::iterator itExistingSelection = itExistingMarket->m_selections.begin();
         itExistingSelection != itExistingMarket->m_selections.end(); itExistingSelection++) {
      if (itNewSelection->m_selectionId == itExistingSelection->m_selectionId) {
        itExistingSelection->m_availableToBackPrice = itNewSelection->m_availableToBackPrice;
        itExistingSelection->m_availableToBackSize = itNewSelection->m_availableToBackSize;
        itExistingSelection->m_availableToLayPrice = itNewSelection->m_availableToLayPrice;
        itExistingSelection->m_availableToLaySize = itNewSelection->m_availableToLaySize;
        itExistingSelection->m_status = itNewSelection->m_status;
        itExistingSelection->m_handicap = itNewSelection->m_handicap;
        foundNewSelection = true;
        break;
      }
    }

    if (!foundNewSelection) {
      itExistingMarket->m_selections.push_back(*itNewSelection);
      qDebug() << "itExistingMarket->m_selections.size()=" << QString::number(itExistingMarket->m_selections.size());
    }
  }
}

bool MarketsData::belowMarketDataRequestLimit(int currentSlot, int numberOfNewMarkets) {
  // Assuming EX_BEST_OFFERS (5 points / market)

  // Count number of markets in group
  int currentMarketCount = 0;
  for (std::list< std::pair<BfEvent, std::list<BetfairMarket> > >::iterator mapIt = m_activeEventMarketsData[currentSlot].begin();
       mapIt != m_activeEventMarketsData[currentSlot].end(); mapIt++) {
    currentMarketCount += mapIt->second.size();
  }

  return (currentMarketCount+numberOfNewMarkets)*5 <= 200;
}
