#ifndef BFACCOUNTSAPIJSONCREATOR_H
#define BFACCOUNTSAPIJSONCREATOR_H

#include <qjsonobject.h>

class BfAccountsApiJsonCreator {
public:
  static void createGetAccountFunds(QJsonObject &jsonObj) {
    jsonObj[QString("jsonrpc")] = QString("2.0");
    jsonObj[QString("id")] = QJsonValue(1);
    jsonObj[QString("method")] = QString("AccountAPING/v1.0/getAccountFunds");

    QJsonObject jsonParams;
    jsonParams[QString("wallet")] = QString("UK");

    jsonObj[QString("params")] = jsonParams;
  }

  static void createGetAccountDetails(QJsonObject &jsonObj) {
    jsonObj[QString("jsonrpc")] = QString("2.0");
    jsonObj[QString("id")] = QJsonValue(1);
    jsonObj[QString("method")] = QString("AccountAPING/v1.0/getAccountDetails");

    QJsonObject jsonParams;

    jsonObj[QString("params")] = jsonParams;
  }
};

#endif // BFACCOUNTSAPIJSONCREATOR_H

