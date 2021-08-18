#ifndef KEEPALIVEAPI_H
#define KEEPALIVEAPI_H

#include <QObject>
#include <QString>

#include <map>

#include "betfairlib_global.h"

#include "misc/bfconfig.h"

#include "betfairapi/httpjsonclient.h"
#include "bftypes/bfapingexception.h"

class BETFAIRLIBSHARED_EXPORT KeepAliveApi : public QObject
{
  Q_OBJECT
public:
  KeepAliveApi(QObject *parent, BfConfig *bfConfig);

  void sendKeepAlive();

private:
  BfConfig *m_bfConfig;
  QNetworkAccessManager m_networkAccessManager;

private slots:
  void replyFinishToken(QNetworkReply *reply);
signals:
  void error(BfApiNgException *ex);

};

#endif // KEEPALIVEAPI_H

