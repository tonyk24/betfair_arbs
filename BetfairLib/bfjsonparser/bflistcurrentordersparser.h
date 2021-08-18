#ifndef BFLISTCURRENTORDERSPARSER_H
#define BFLISTCURRENTORDERSPARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>

#include "bfjsonparser/bfapingexceptionparser.h"
#include "bftypes/bfapingexception.h"
#include "bftypes/bfcurrentorder.h"

class BfListCurrentOrdersParser {
public:
  BfListCurrentOrdersParser() {
  }

  static BfApiNgException * parse(const QString &answer,
                                  std::list<BfCurrentOrder> &currentOrdersList) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObj = jsonResponse.object();

    /*
    "{\"jsonrpc\":\"2.0\",\
    "result\":
    {\"currentOrders\":
    [{\"betId\":\"77172245652\",
    \"marketId\":\"1.127665149\",
    \"selectionId\":47972,
    \"handicap\":0.0,
    \"priceSize\":
     {\"price\":2.06,
      \"size\":228.57},
    \"bspLiability\":0.0,
    \"side\":\"LAY\",
    \"status\":\"EXECUTION_COMPLETE\",
    \"persistenceType\":\"LAPSE\",
    \"orderType\":\"LIMIT\",
    \"placedDate\":\"2016-10-17T13:23:37.000Z\",
    \"matchedDate\":\"2016-10-17T13:23:37.000Z\",
    \"averagePriceMatched\":2.06,
    \"sizeMatched\":228.57,
    \"sizeRemaining\":0.0,
    \"sizeLapsed\":0.0,
    \"sizeCancelled\":0.0,
    \"sizeVoided\":0.0,
    \"regulatorCode\":\"MALTA LOTTERIES AND GAMBLING AUTHORITY\"}
    ],
    \"moreAvailable\":false},\"id\":1}"
     * */

    // Parse
    if (jsonObj["error"].isObject()) {
      return BfApiNgExceptionParser::parseException(answer);
    } else if (jsonObj["result"].isObject()) {

      QJsonObject resultObj = jsonObj["result"].toObject();


      QJsonArray currentOrders = resultObj[QString("currentOrders")].toArray();
      for (QJsonArray::iterator it = currentOrders.begin();
           it != currentOrders.end(); it++) {
        BfCurrentOrder currentOrder;
        QJsonObject bfCurrentOrderJsonObj = (*it).toObject();

        if (bfCurrentOrderJsonObj.contains(QString("betId"))) {
          currentOrder.m_betId = bfCurrentOrderJsonObj["betId"].toString();
        }
        currentOrder.m_marketId = bfCurrentOrderJsonObj["marketId"].toString();
        // TODO: Valid conversion ??
        qint64 selId = (qint64)bfCurrentOrderJsonObj[QString("selectionId")].toDouble();
        currentOrder.m_selectionId = selId;
        if (bfCurrentOrderJsonObj.contains(QString("handicap"))) {
          currentOrder.m_handicap = bfCurrentOrderJsonObj[QString("handicap")].toDouble();
        }
        currentOrder.m_side = BfSide::toEnum(bfCurrentOrderJsonObj[QString("side")].toString());
        currentOrder.m_status = BfOrderStatus::toEnum(bfCurrentOrderJsonObj["status"].toString());
        currentOrder.m_persistenceType = BfPersistenceType::toEnum(bfCurrentOrderJsonObj[QString("persistenceType")].toString());
        currentOrder.m_orderType = BfOrderType::toEnum(bfCurrentOrderJsonObj[QString("orderType")].toString());
        if (bfCurrentOrderJsonObj.contains(QString("placedDate"))) {
          QDateTime placeDate = QDateTime::fromString(bfCurrentOrderJsonObj["placedDate"].toString(),
              "yyyy-MM-ddThh:mm:ss.zzzZ");
          placeDate.setTimeSpec(Qt::UTC);
          currentOrder.m_placeDate = placeDate;
        }
        if (bfCurrentOrderJsonObj.contains(QString("matchedDate"))) {
          QDateTime matchedDate = QDateTime::fromString(bfCurrentOrderJsonObj["matchedDate"].toString(),
              "yyyy-MM-ddThh:mm:ss.zzzZ");
          matchedDate.setTimeSpec(Qt::UTC);
          currentOrder.m_matchedDate = matchedDate;
        }
        currentOrder.m_averagePriceMatched = bfCurrentOrderJsonObj[QString("averagePriceMatched")].toDouble();
        currentOrder.m_sizeMatched = bfCurrentOrderJsonObj[QString("sizeMatched")].toDouble();

        currentOrdersList.push_back(currentOrder);
      }
    }
    else {
      return NEW_INTERNAL_EXCEPTION("Excpeting result array");
    }

    return 0;
  }
};

#endif // BFLISTCURRENTORDERSPARSER_H

