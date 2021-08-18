#ifndef BFLISTCURRENTORDERSJSONCREATOR_H
#define BFLISTCURRENTORDERSJSONCREATOR_H

#include <list>
#include <qjsonobject.h>
#include <QString>

class BfListCurrentOrdersJsonCreator
{
public:
  static void create(std::list<QString> marketIds,
      QJsonObject &jsonObj) {
    /* Example
[{"jsonrpc": "2.0",
  "method":
  "SportsAPING/v1.0/listCurrentOrders",
  "params":
  {
    "marketIds":
       ["1.127665149"],
     "dateRange":{}
  },
  "id": 1}]
     * */
    jsonObj[QString("jsonrpc")] = QString("2.0");
    jsonObj[QString("id")] = QJsonValue(1);
    jsonObj[QString("method")] = QString("SportsAPING/v1.0/listCurrentOrders");

    QJsonObject jsonParams;
    QJsonArray jsonArray;
    for(std::list<QString>::iterator it = marketIds.begin();
        it != marketIds.end(); it++)
    {
      jsonArray.append(QJsonValue(*it));
    }
    jsonParams[QString("marketIds")] = jsonArray;


    jsonObj[QString("params")] = jsonParams;
  }
};

#endif // BFLISTCURRENTORDERSJSONCREATOR_H
