#include "betfairapi/accountsapi.h"

#include "bfjsoncreator/bfaccountsapijsoncreator.h"
#include "bfjsonparser/bfaccountsapiparser.h"

AccountsApi::AccountsApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig),
  m_httpJsonClientFunds(0, bfConfig, "https://api.betfair.com/exchange/account/json-rpc/v1"),
  m_httpJsonClientDetails(0, bfConfig, "https://api.betfair.com/exchange/account/json-rpc/v1"){
  Q_UNUSED(parent);

  QObject::connect(&m_httpJsonClientFunds, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinishFunds(QString)));

  QObject::connect(&m_httpJsonClientFunds, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));

  QObject::connect(&m_httpJsonClientDetails, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinishDetails(QString)));

  QObject::connect(&m_httpJsonClientDetails, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
}

void AccountsApi::getAccountFunds() {
  QJsonObject jsonObj;

  BfAccountsApiJsonCreator::createGetAccountFunds(jsonObj);
  m_httpJsonClientFunds.send(jsonObj);
}

void AccountsApi::getAccountDetails() {
  QJsonObject jsonObj;

  BfAccountsApiJsonCreator::createGetAccountDetails(jsonObj);
  m_httpJsonClientDetails.send(jsonObj);
}


void AccountsApi::replyFinishFunds(QString answer) {
  BfAccountFundsRsp accountFundsRsp;
  BfApiNgException *apiNgEx = BfAccountsApiParser::parseGetAccountFunds(answer, accountFundsRsp);

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  } else {
    emit valueChanged(accountFundsRsp);
  }
}

void AccountsApi::replyFinishDetails(QString answer) {
  BfAccountDetailsRsp accountDetailsRsp;
  BfApiNgException *apiNgEx = BfAccountsApiParser::parseGetAccountDetails(answer, accountDetailsRsp);

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  } else {
    emit valueChanged(accountDetailsRsp);
  }
}

void AccountsApi::errorOccurred(BfApiNgException *ex) {
  emit error(ex);
}
