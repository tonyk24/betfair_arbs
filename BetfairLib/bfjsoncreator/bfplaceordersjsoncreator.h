#ifndef BFPLACEORDERSJSONCREATOR_H
#define BFPLACEORDERSJSONCREATOR_H

#include <list>

#include <QString>
#include <QJsonObject>
#include <QJsonArray>

#include "bftypes/bfplaceinstruction.h"

class BfPlaceOrdersJsonCreator {
public:
  BfPlaceOrdersJsonCreator() {
  }

  static void create(const QString &marketId,
                     const std::list<BfPlaceInstruction> &placeInstructions,
                     QJsonObject &jsonObj) {
    jsonObj[QString("jsonrpc")] = QString("2.0");
    jsonObj[QString("id")] = QJsonValue(1);
    jsonObj[QString("method")] = QString("SportsAPING/v1.0/placeOrders");

    QJsonObject jsonParams;
    jsonParams[QString("marketId")] = marketId;

    QJsonArray jsonArrayInstructions;

    // Fill instructions
    for (std::list<BfPlaceInstruction>::const_iterator it = placeInstructions.begin();
         it != placeInstructions.end(); it++) {
      QJsonObject jsonObjPlaceInstruction;
      jsonObjPlaceInstruction[QString("orderType")] = BfOrderType::toStr(it->m_orderType);
      jsonObjPlaceInstruction[QString("selectionId")] = QString::number(it->m_selectionId);
      jsonObjPlaceInstruction[QString("handicap")] = QString::number(it->m_handicap);
      jsonObjPlaceInstruction[QString("side")] = BfSide::toStr(it->m_side);

      QJsonObject jsonObjLimitOrder;
      jsonObjLimitOrder[QString("size")] = QString::number(it->m_limitOrder.m_size);
      jsonObjLimitOrder[QString("price")] = QString::number(it->m_limitOrder.m_price);
      jsonObjLimitOrder[QString("persistenceType")] = BfPersistenceType::toStr(it->m_limitOrder.m_persistenceType);
      jsonObjPlaceInstruction[QString("limitOrder")] = jsonObjLimitOrder;
      jsonArrayInstructions.append(jsonObjPlaceInstruction);
    }

    jsonParams[QString("instructions")] = jsonArrayInstructions;

    jsonObj[QString("params")] = jsonParams;
  }
};

#endif // BFPLACEORDERSJSONCREATOR_H

