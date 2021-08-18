#ifndef BFPLACEINSTRUCTION_H
#define BFPLACEINSTRUCTION_H

#include "bfenums/bfordertype.h"
#include "bfenums/bfside.h"
#include "bftypes/bflimitorder.h"
#include "bftypes/bflimitoncloseorder.h"
#include "bftypes/bfmarketoncloseorder.h"

class BfPlaceInstruction {
public:
  BfPlaceInstruction() {
  }

  BfPlaceInstruction(BfOrderType::Enum orderType,
                     qint64 selectionId,
                     double handicap,
                     BfSide::Enum side,
                     BfLimitOrder limitOrder) :
    m_orderType(orderType),
    m_selectionId(selectionId),
    m_handicap(handicap),
    m_side(side),
    m_limitOrder(limitOrder)
  {
  }

  QString toStr() const {
    return QString("BfPlaceInstruction(orderType=%1, selId=%2, handicap=%3, side=%4 limitOrder=%5)")
        .arg(BfOrderType::toStr(m_orderType),
             QString::number(m_selectionId),
             QString::number(m_handicap),
             BfSide::toStr(m_side),
             m_limitOrder.toStr());
  }



  BfOrderType::Enum m_orderType;
  qint64 m_selectionId;
  double m_handicap;
  BfSide::Enum m_side;

  BfLimitOrder m_limitOrder;
};

#endif // BFPLACEINSTRUCTION_H

