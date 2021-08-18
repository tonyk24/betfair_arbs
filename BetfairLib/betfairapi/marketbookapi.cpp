#include "betfairapi/marketbookeapi.h"
#include "bftypes/bfmarket.h"
#include "bfenums/bfmarketstatus.h"
#include "bftypes/bfapingexception.h"
#include "bfjsonparser/bfapingexceptionparser.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

MarketBookApi::MarketBookApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig),
  m_httpJsonClient(0, bfConfig, "https://api.betfair.com/exchange/betting/json-rpc/v1") {
  Q_UNUSED(parent);


  QObject::connect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinish(QString)));

  // Error
  QObject::connect(&m_httpJsonClient, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
}

void MarketBookApi::getMarketBook(std::list<QString> marketsToGet) {
  QJsonObject jsonObj;
  jsonObj[QString("jsonrpc")] = QString("2.0");
  jsonObj[QString("id")] = QJsonValue(1);

  jsonObj[QString("method")] = QString("SportsAPING/v1.0/listMarketBook");

  /*
      [{"jsonrpc": "2.0", "method": "SportsAPING/v1.0/listMarketBook",
      "params":
          {"currencyCode":"SEK",
           "marketIds":["1.118760944"],
           "priceProjection":{"priceData":["SP_AVAILABLE"]}}, "id": 1}]"
   * */
  QJsonObject jsonObjParams;

  QJsonArray jsonArray;

  for (std::list<QString>::iterator it = marketsToGet.begin();
       it != marketsToGet.end(); it++) {
    jsonArray.append(QJsonValue(*it));
  }

  jsonObjParams[QString("marketIds")] = jsonArray;
  jsonObjParams[QString("currencyCode")] = QJsonValue(QString("SEK"));

  QJsonObject jsonObjPriceProjection;

  QJsonArray priceDataArray;
  priceDataArray.append(QJsonValue(QString("EX_BEST_OFFERS")));
  jsonObjPriceProjection[QString("priceData")] = priceDataArray;

  jsonObjParams[QString("priceProjection")] = jsonObjPriceProjection;

  jsonObj[QString("params")] = jsonObjParams;

  m_httpJsonClient.send(jsonObj);
}

void MarketBookApi::replyFinish(QString answer) {

  std::list<BetfairMarket> newMarkets;
  /*
        [{"jsonrpc":"2.0",
          "result":[
            {"marketId":"1.118760944","isMarketDataDelayed":true,"status":"OPEN","betDelay":0,"bspReconciled":false,"complete":true,"inplay":false,"numberOfWinners":1,"numberOfRunners":2,"numberOfActiveRunners":2,"totalMatched":0.0,"totalAvailable":2739.85,"crossMatching":true,"runnersVoidable":false,"version":986303272,
             "runners":[
               {"selectionId":47972,"handicap":0.0,"status":"ACTIVE","totalMatched":0.0,
                  "ex":{"availableToBack":[{"price":1.02,"size":1244.3},
                                           {"price":1.01,"size":1221.23}],
                        "availableToLay":[],"tradedVolume":[]}},
               {"selectionId":47973,"handicap":0.0,"status":"ACTIVE","totalMatched":0.0,
                  "ex":{
                        "availableToBack":[{"price":1.01,"size":235.91}],
                        "availableToLay":[{"price":110.0,"size":34.89}],
                  "tradedVolume":[]}}]}],"id":1}]"
    */

  QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

  if (!jsonResponse.isObject()) {
    qWarning() << "expecting object...";
    return;
  }
  QJsonObject jsonObj = jsonResponse.object();

  BfApiNgException *apiNgEx = 0;

  if (jsonObj["error"].isObject()) {
    apiNgEx = BfApiNgExceptionParser::parseException(answer);
  } else if (jsonObj["result"].isArray())
  {
    QJsonArray jsonArray = jsonObj["result"].toArray();
    for (QJsonArray::iterator it = jsonArray.begin();
         it != jsonArray.end(); it++) {
      QJsonObject marketObj = (*it).toObject();
      QString marketId = QString(marketObj["marketId"].toString());
      QString marketStatus = QString(marketObj["status"].toString());
      BetfairMarket market(marketId, 0.0);
      market.m_marketStatus = BfMarketStatus::toEnum(marketStatus);
      if (marketObj["runners"].isArray()) {
        QJsonArray runnersArray = marketObj["runners"].toArray();
        parseRunnersJsonArray(runnersArray, &market);
      }
      else {
        qWarning() << "expecting array-...";
        return;
      }
      newMarkets.push_back(market);
    }
  }
  else {
    qWarning() << "Expectom object= " << answer;
    return;
  }

  if (apiNgEx != 0) {
    qWarning() << ">>" << __PRETTY_FUNCTION__ << ":" << __FILE__ << ":" << QString::number(__LINE__);
    qWarning() << apiNgEx->toString();
    emit error(apiNgEx);
  }

  emit valueChanged(newMarkets);
}

void MarketBookApi::parseRunnersJsonArray(QJsonArray &runnersArray, BetfairMarket *market) {
  for (QJsonArray::iterator itRunner = runnersArray.begin();
       itRunner != runnersArray.end(); itRunner++) {
    QJsonObject runnersObj = (*itRunner).toObject();

    qint64 selectionId = (qint64)runnersObj["selectionId"].toDouble();
    double handicap = runnersObj["handicap"].toDouble();

    QString selStatus = runnersObj["status"].toString();
    std::vector<double> backPrice;
    std::vector<double> backSize;
    std::vector<double> layPrice;
    std::vector<double> laySize;

    QJsonObject exObj = runnersObj["ex"].toObject();

    QJsonArray backArray = exObj["availableToBack"].toArray();

    int counter = 1;
    for (QJsonArray::const_iterator itAvailableBack = backArray.begin();
         itAvailableBack != backArray.end(); itAvailableBack++, counter++) {
      QJsonObject backObj = (*itAvailableBack).toObject();
      backPrice.push_back(backObj["price"].toDouble());
      backSize.push_back(backObj["size"].toDouble());
      if (counter >= 3) {
       break; // Only store three first
      }
    }

    QJsonArray layArray = exObj["availableToLay"].toArray();

    counter = 1;
    for (QJsonArray::const_iterator itAvailableLay = layArray.begin();
         itAvailableLay != layArray.end(); itAvailableLay++, counter++) {
      QJsonObject layObj = (*itAvailableLay).toObject();
      layPrice.push_back(layObj["price"].toDouble());
      laySize.push_back(layObj["size"].toDouble());
      if (counter >= 3) {
        break; // Only store three first
      }
    }
    BetfairSelection sel(selectionId, "");
    sel.m_status = selStatus;
    sel.m_handicap = handicap;
    sel.m_availableToBackPrice = backPrice;
    sel.m_availableToBackSize = backSize;
    sel.m_availableToLayPrice = layPrice;
    sel.m_availableToLaySize = laySize;
    market->m_selections.push_back(sel);
  }
}

void MarketBookApi::errorOccurred(BfApiNgException *ex) {
  emit error(ex);
}


