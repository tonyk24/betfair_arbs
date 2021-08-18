#ifndef CANCELORDERSAPI_H
#define CANCELORDERSAPI_H


#include <list>

#include <QObject>
#include <QString>
#include <QNetworkReply>

#include "betfairlib_global.h"

#include "misc/bfconfig.h"

#include "bftypes/bfmarket.h"

#include "bftypes/bfcancelexecutionreport.h"
#include "bftypes/bfcancelinstruction.h"
#include "betfairapi/httpjsonclient.h"

#include "bftypes/bfapingexception.h"

class BETFAIRLIBSHARED_EXPORT CancelOrdersApi : public QObject
{
  Q_OBJECT
public:
  CancelOrdersApi(QObject *parent, BfConfig *bfConfig);

  void cancelOrders(QString marketId, std::list<BfCancelInstruction> instructions);
private:
  BfConfig *m_bfConfig;
  HttpJsonClient m_httpJsonClient;

public slots:
  void replyFinish(QString answer);
  void errorOccurred(BfApiNgException *ex);
signals:
  void cancelOrdersResponse(BfCancelExecutionReport cancelExecutionReport);
  void error(BfApiNgException *ex);

};

#endif // CANCELORDERSAPI_H
