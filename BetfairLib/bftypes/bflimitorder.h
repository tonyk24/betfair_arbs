#ifndef BFLIMITORDER_H
#define BFLIMITORDER_H

#include "bfenums/bfpersistencetype.h"

class BfLimitOrder {
public:
  BfLimitOrder() {

  }

  BfLimitOrder(double price, double size, BfPersistenceType::Enum persistenceType) :
    m_price(price),
    m_size(size),
    m_persistenceType(persistenceType)
  {

  }

  QString toStr() const {
    return QString("BfLimitOrder(pr=%1, size=%2, %3)")
        .arg(QString::number(m_price),
             QString::number(m_size),
             BfPersistenceType::toStr(m_persistenceType));
  }

  bool operator==(const BfLimitOrder &other) const {
    return (this->m_price == other.m_price) &&
        (this->m_size == other.m_size) &&
        (this->m_persistenceType == other.m_persistenceType);
  }

  double m_price;
  double m_size;

  BfPersistenceType::Enum m_persistenceType;
};

#endif // BFLIMITORDER_H

