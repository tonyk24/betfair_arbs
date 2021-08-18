#ifndef BFACCOUNTSAPIPARSER_H
#define BFACCOUNTSAPIPARSER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

#include "bftypes/bfapingexception.h"
#include "bftypes/bfaccountdetailsrsp.h"
#include "bftypes/bfaccountfundsrsp.h"

#include "bfjsonparser/bfapingexceptionparser.h"

class BfAccountsApiParser {
public:
  BfAccountsApiParser() {
  }

  static BfApiNgException * parseGetAccountFunds(const QString &answer,
                                  BfAccountFundsRsp & accountFundsRsp) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObj = jsonResponse.object();

    // Parse
    if (jsonObj["error"].isObject()) {
      return BfApiNgExceptionParser::parseException(answer);
    } else if (jsonObj["result"].isObject()) {
/*
{"jsonrpc":"2.0","result":
{
"availableToBetBalance":355.89,
"exposure":3.0,
"retainedCommission":2.0,
"exposureLimit":-50000.0,
"discountRate":1.0,
"pointsBalance":10,
"wallet":"UK"},"id":1}

 * */
      QJsonObject resultObj = jsonObj["result"].toObject();

      accountFundsRsp.m_availableToBetBalance =  resultObj[QString("availableToBetBalance")].toDouble();
      accountFundsRsp.m_exposure =               resultObj[QString("exposure")].toDouble();
      accountFundsRsp.m_retainedCommission =     resultObj[QString("retainedCommission")].toDouble();
      accountFundsRsp.m_exposureLimit =          resultObj[QString("exposureLimit")].toDouble();
      accountFundsRsp.m_discountRate =           resultObj[QString("discountRate")].toDouble();
      accountFundsRsp.m_pointsBalance =          resultObj[QString("pointsBalance")].toInt();
    } else {
      return NEW_INTERNAL_EXCEPTION("Excpeting result array");
    }

    return 0;
  }

  static BfApiNgException * parseGetAccountDetails(const QString &answer,
                                  BfAccountDetailsRsp & accountDetailsRsp) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObj = jsonResponse.object();

    // Parse
    if (jsonObj["error"].isObject()) {
      return BfApiNgExceptionParser::parseException(answer);
    } else if (jsonObj["result"].isObject()) {
      QJsonObject resultObj = jsonObj["result"].toObject();

      accountDetailsRsp.m_currencyCode =  resultObj[QString("currencyCode")].toString();
      accountDetailsRsp.m_firstName =     resultObj[QString("firstName")].toString();
      accountDetailsRsp.m_lastName =      resultObj[QString("lastName")].toString();
      accountDetailsRsp.m_localeCode =    resultObj[QString("localeCode")].toString();
      accountDetailsRsp.m_region =        resultObj[QString("region")].toString();
      accountDetailsRsp.m_timezone =      resultObj[QString("timezone")].toString();
      accountDetailsRsp.m_discountRate =  resultObj[QString("discountRate")].toDouble();
      accountDetailsRsp.m_pointsBalance = resultObj[QString("pointsBalance")].toInt();
      accountDetailsRsp.m_countryCode =   resultObj[QString("countryCode")].toString();

/*
{"jsonrpc":"2.0","result":{
"currencyCode":"SEK",
"firstName":"Tony",
"lastName":"Karlsson",
"localeCode":"sv",
"region":"GBR",
"timezone":"Europe/London",
"discountRate":1.0,
"pointsBalance":10,
"countryCode":"SE"},"id":1}

 * */
    } else {
      return NEW_INTERNAL_EXCEPTION("Excpeting result array");
    }

    return 0;
  }
};

#endif // BFACCOUNTSAPIPARSER_H

