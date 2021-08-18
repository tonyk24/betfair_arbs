#ifndef BFCANCELORDERSPARSER_H
#define BFCANCELORDERSPARSER_H


#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>

#include "bfjsonparser/bfapingexceptionparser.h"
#include "bftypes/bfapingexception.h"
#include "bftypes/bfcancelexecutionreport.h"
#include "bftypes/bfcancelinstructionreport.h"

class BfCancelOrdersParser {
public:
  BfCancelOrdersParser() {
  }

  static BfApiNgException * parse(const QString &answer,
                                  BfCancelExecutionReport &cancelExecutionReport) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObj = jsonResponse.object();


    // Parse
    if (jsonObj["error"].isObject()) {
      return BfApiNgExceptionParser::parseException(answer);
    } else if (jsonObj["result"].isObject()) {

      QJsonObject resultObj = jsonObj["result"].toObject();

      cancelExecutionReport.m_status = BfExecutionReportStatus::toEnum(resultObj[QString("status")].toString());

      if (resultObj.contains(QString("errorCode"))) {
        cancelExecutionReport.m_errorCode = BfExecutionErrorReportCode::toEnum(resultObj[QString("errorCode")].toString());
      }

      cancelExecutionReport.m_marketId = resultObj["marketId"].toString();

      QJsonArray instReports = resultObj[QString("instructionReports")].toArray();
      for (QJsonArray::iterator it = instReports.begin();
           it != instReports.end(); it++) {

        BfCancelInstructionReport bfCancelReport;
        QJsonObject bfPlReportQJsonObj = (*it).toObject();
        bfCancelReport.m_status = BfInstructionReportStatus::toEnum(bfPlReportQJsonObj["status"].toString());
        if (bfPlReportQJsonObj.contains(QString("errorCode"))) {
          bfCancelReport.m_errorCode = BfInstructionReportErrorCode::toEnum(bfPlReportQJsonObj["errorCode"].toString());

          QJsonObject instructionJsonObj = bfPlReportQJsonObj["errorCode"].toObject();
          bfCancelReport.m_instruction.m_betId = instructionJsonObj["betId"].toString();
          bfCancelReport.m_instruction.m_sizeReduction = instructionJsonObj["sizeReduction"].toString().toDouble();

          bfCancelReport.m_sizeCancelled = bfPlReportQJsonObj["cancelledDate"].toString().toDouble();
          bfCancelReport.m_cancelledDate = QDateTime::fromString(bfPlReportQJsonObj["cancelledDate"].toString());
        }
      }



    }
    else {
      return NEW_INTERNAL_EXCEPTION("Excpeting result array");
    }

    return 0;
  }
};

#endif // BFCANCELORDERSPARSER_H

