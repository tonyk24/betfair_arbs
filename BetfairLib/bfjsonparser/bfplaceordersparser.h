#ifndef BFPLACEORDERSPARSER_H
#define BFPLACEORDERSPARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>

#include "bfjsonparser/bfplaceordersparser.h"
#include "bfjsonparser/bfapingexceptionparser.h"
#include "bftypes/bfapingexception.h"
#include "bftypes/bfplaceexecutionreport.h"
#include "bftypes/bfplaceinstructionreport.h"

class BfPlaceOrdersParser {
public:
  BfPlaceOrdersParser() {
  }

  static BfApiNgException * parse(const QString &answer,
                                  BfPlaceExecutionReport & executionReport) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObj = jsonResponse.object();

    // Parse
    if (jsonObj["error"].isObject()) {
      return BfApiNgExceptionParser::parseException(answer);
    } else if (jsonObj["result"].isObject()) {
      QJsonObject resultObj = jsonObj["result"].toObject();

      executionReport.m_status = BfExecutionReportStatus::toEnum(resultObj[QString("status")].toString());

      if (resultObj.contains(QString("errorCode"))) {
        executionReport.m_errorCode = BfExecutionErrorReportCode::toEnum(resultObj[QString("errorCode")].toString());
      }

      executionReport.m_marketId = resultObj["marketId"].toString();

      QJsonArray instReports = resultObj[QString("instructionReports")].toArray();
      for (QJsonArray::iterator it = instReports.begin();
           it != instReports.end(); it++) {
        BfPlaceInstructionReport bfPlReport;
        QJsonObject bfPlReportQJsonObj = (*it).toObject();
        bfPlReport.m_status = BfInstructionReportStatus::toEnum(bfPlReportQJsonObj["status"].toString());
        if (bfPlReportQJsonObj.contains(QString("errorCode"))) {
          bfPlReport.m_errorCode = BfInstructionReportErrorCode::toEnum(bfPlReportQJsonObj["errorCode"].toString());
        }
        QJsonObject reportInstJsonObj = bfPlReportQJsonObj[QString("instruction")].toObject();
        if (bfPlReportQJsonObj.contains(QString("betId"))) {
          bfPlReport.m_betId = bfPlReportQJsonObj["betId"].toString();
        }
        if (bfPlReportQJsonObj.contains(QString("averagePriceMatched"))) {
          bfPlReport.m_averagePriceMatched = bfPlReportQJsonObj["averagePriceMatched"].toDouble();
        }
        if (bfPlReportQJsonObj.contains(QString("sizeMatched"))) {
          bfPlReport.m_sizeMatched = bfPlReportQJsonObj["sizeMatched"].toDouble();
        }
        if (bfPlReportQJsonObj.contains(QString("placedDate"))) {
          QDateTime placeDate = QDateTime::fromString(bfPlReportQJsonObj["placedDate"].toString(),
              "yyyy-MM-ddThh:mm:ss.zzzZ");
          placeDate.setTimeSpec(Qt::UTC);
          bfPlReport.m_placeDate = placeDate;
        }

        // TODO: Valid conversion ??
        qint64 selId = (qint64)reportInstJsonObj[QString("selectionId")].toDouble();
        bfPlReport.m_placeInstruction.m_selectionId = selId;
        bfPlReport.m_placeInstruction.m_orderType = BfOrderType::toEnum(reportInstJsonObj[QString("orderType")].toString());
        bfPlReport.m_placeInstruction.m_side = BfSide::toEnum(reportInstJsonObj[QString("side")].toString());

        if (reportInstJsonObj.contains(QString("handicap"))) {
          bfPlReport.m_placeInstruction.m_handicap = reportInstJsonObj[QString("handicap")].toDouble();
        }

        if (reportInstJsonObj.contains("limitOrder")) {
          QJsonObject limitOrderObj = reportInstJsonObj[QString("limitOrder")].toObject();
          bfPlReport.m_placeInstruction.m_limitOrder.m_price = limitOrderObj[QString("price")].toDouble();
          bfPlReport.m_placeInstruction.m_limitOrder.m_size = limitOrderObj[QString("size")].toDouble();
          bfPlReport.m_placeInstruction.m_limitOrder.m_persistenceType = BfPersistenceType::toEnum(limitOrderObj[QString("persistenceType")].toString());
          executionReport.m_instructionReports.push_back(bfPlReport);
        }
      }

      /*
[{"jsonrpc":"2.0","result":
  {"status":"SUCCESS",
   "marketId":"1.120224362",
   "instructionReports":[{"status":"SUCCESS",
                          "instruction":{"selectionId":1222679,
                                          "handicap":0.0,
                                          "limitOrder":
                                              {"size":30.0,
                                               "price":1.07,
                                               "persistenceType":"LAPSE"},
                                        "orderType":"LIMIT",
                                        "side":"BACK"},
            "betId":"54512223950",
             "placedDate":"2015-08-26T20:37:14.000Z",
             "averagePriceMatched":1.69,
             "sizeMatched":30.0}]},
          "id":1}
    ]

       * */
    }
    else {
      return NEW_INTERNAL_EXCEPTION("Excpeting result array");
    }

    return 0;
  }
};

#endif // BFPLACEORDERSPARSER_H

