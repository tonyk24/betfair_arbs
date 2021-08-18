#ifndef ACCOUNTSAPI_H
#define ACCOUNTSAPI_H

#include "betfairlib_global.h"

#include "betfairapi/httpjsonclient.h"

#include "misc/bfconfig.h"

#include "bftypes/bfapingexception.h"
#include "bftypes/bfaccountfundsrsp.h"
#include "bftypes/bfaccountdetailsrsp.h"

class BETFAIRLIBSHARED_EXPORT AccountsApi : public QObject
{
  Q_OBJECT
public:
  AccountsApi(QObject *parent, BfConfig *bfConfig);

  void getAccountFunds();
  void getAccountDetails();

private:
  BfConfig *m_bfConfig;
  HttpJsonClient m_httpJsonClientFunds;
  HttpJsonClient m_httpJsonClientDetails;


public slots:
  void replyFinishFunds(QString answer);
  void replyFinishDetails(QString answer);
  void errorOccurred(BfApiNgException *ex);
signals:
  void valueChanged(BfAccountFundsRsp accountFundsRsp);
  void valueChanged(BfAccountDetailsRsp accountFundsRsp);
  void error(BfApiNgException *ex);
};


#endif // ACCOUNTSAPI_H

