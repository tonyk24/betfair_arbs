#ifndef BFAPINGEXCEPTIONPARSER_H
#define BFAPINGEXCEPTIONPARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "bftypes/bfapingexception.h"

/*
{"jsonrpc":"2.0","error":
    {"code":-32099,
     "message":"ANGX-0001",
     "data":
          {"exceptionname":"APINGException",
           "APINGException":
              {"errorDetails":"",
               "errorCode":"TOO_MUCH_DATA",
               "requestUUID":"prdang044-07291214-005a69b6ce"
               }
          }
     },
  "id":1}
*/

class BfApiNgExceptionParser {
public:
  static BfApiNgException * parseException(const QString &answer) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObj = jsonResponse.object();

    if (jsonObj["error"].isObject())
    {
      QJsonObject errObj = jsonObj["error"].toObject();

      int code = errObj["code"].toInt();
      QString message = errObj["message"].toString();

      QString errorDetails = "";
      QString errorCode = "";
      QString requestUUID = "";

      if (errObj["data"].isObject()) {
        QJsonObject errDataObj = errObj["data"].toObject();
        if (errDataObj["APINGException"].isObject()) {
          QJsonObject apNgEXObj = errDataObj["APINGException"].toObject();
          errorDetails = apNgEXObj["errorDetails"].toString();
          errorCode = apNgEXObj["errorCode"].toString();
          requestUUID = apNgEXObj["requestUUID"].toString();
        }
      }

      BfApiNgException *apiNgEx = NEW_NG_EXCPETION(code, message, errorDetails,
                                                       errorCode, requestUUID);
      return apiNgEx;
    }
    else {
      return NEW_INTERNAL_EXCEPTION("Expecting error object");
    }
    return 0;
  }
};

#endif // BFAPINGEXCEPTIONPARSER_H
