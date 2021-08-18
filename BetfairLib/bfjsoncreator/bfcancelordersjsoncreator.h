#ifndef BFCANCELORDERSJSONCREATOR_H
#define BFCANCELORDERSJSONCREATOR_H

#include <map>
#include <list>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

#include "bftypes/bfcancelinstruction.h"

class BfCancelOrdersJsonCreator
{
public:
  static void create(QString marketId, std::list<BfCancelInstruction> instructions,
                     QJsonObject &jsonObj) {
    /* Example
     [{"jsonrpc": "2.0",
       "method": "SportsAPING/v1.0/cancelOrders",
       "params": {"marketId":"1.127907953",
       "instructions":[{"betId":"111","sizeReduction":null}]}, "id": 1}]
     * */
    jsonObj[QString("jsonrpc")] = QString("2.0");
    jsonObj[QString("id")] = QJsonValue(1);
    jsonObj[QString("method")] = QString("SportsAPING/v1.0/cancelOrders");

    QJsonObject jsonParams;
    QJsonArray jsonArrayInstructions;
    QJsonObject jsonObjInstruction;
    for (std::list<BfCancelInstruction>::iterator it = instructions.begin();
         it != instructions.end(); it++)
    {
      jsonObj[QString("betId")] = QJsonValue(it->m_betId);
      jsonArrayInstructions.push_back(jsonObjInstruction);
    }
    jsonParams[QString("marketId")] = QJsonValue(marketId);
    jsonParams[QString("instructions")] = jsonArrayInstructions;

    jsonObj[QString("params")] = jsonParams;
  }
};

#endif // BFCANCELORDERSJSONCREATOR_H

