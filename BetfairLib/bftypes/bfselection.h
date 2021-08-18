#ifndef BETFAIRSELECTION_H
#define BETFAIRSELECTION_H

#include <QtGlobal>
#include <vector>
#include <utility>

class BetfairSelection {
public:
  BetfairSelection(qint64 selectionId,
                   QString selectionName):
    m_selectionId(selectionId),
    m_selectionName(selectionName),
    m_handicap(0.0)
  {
    resetData();
  }

  void resetData() {
    m_status = "";
    m_availableToBackPrice.clear();
    m_availableToBackSize.clear();
    m_availableToLayPrice.clear();
    m_availableToLaySize.clear();
  }

  std::pair<double, double> getBack() const {
    if (!m_availableToBackPrice.empty() &&
        !m_availableToBackSize.empty()) {
      return std::make_pair(m_availableToBackPrice[0],
                            m_availableToBackSize[0]);
    }

    return std::make_pair(-1.0, -1.0);
  }

  std::pair<double, double> getLay() const {
    if (!m_availableToLayPrice.empty() &&
        !m_availableToLaySize.empty()) {
      return std::make_pair(m_availableToLayPrice[0],
                            m_availableToLaySize[0]);
    }

    return std::make_pair(-1.0, -1.0);
  }

  qint64 m_selectionId;
  QString m_selectionName;
  QString m_status;
  double m_handicap;
  std::vector<double> m_availableToBackPrice;
  std::vector<double> m_availableToBackSize;
  std::vector<double> m_availableToLayPrice;
  std::vector<double> m_availableToLaySize;
};

#endif // BETFAIRSELECTION_H

