#ifndef APINGEXCEPTION
#define APINGEXCEPTION

#include <QString>
#include <QDebug>
/*
"{"jsonrpc":"2.0","error":
    {"code":-32099,"message":"ANGX-0001",
        "data":
          {"exceptionname":"APINGException",
              "APINGException":{
                    "errorDetails":"",
                    "errorCode":"TOO_MUCH_DATA",
                    "requestUUID":"prdang044-07291214-005a69b6ce"}}},"id":1}"
*/


#define NEW_NG_EXCPETION(code, message, errorDetails, errorCode, requestUUID)   \
    new BfApiNgException((code), (message), (errorDetails),                     \
    (errorCode), (requestUUID),                                                 \
    QString("[%1, %2:%3]")                                                      \
    .arg(__PRETTY_FUNCTION__, __FILE__, QString::number(__LINE__)), "")         \

#define NEW_NG_EXCPETION_EV(code, message, errorDetails, errorCode, requestUUID, eventId)   \
    new BfApiNgException((code), (message), (errorDetails),                     \
    (errorCode), (requestUUID),                                                 \
    QString("[%1, %2:%3]")                                                      \
    .arg(__PRETTY_FUNCTION__, __FILE__, QString::number(__LINE__)),             \
    (eventId))             \

#define NEW_INTERNAL_EXCEPTION(errorDesc)                                       \
    new BfApiNgException((errorDesc),                                           \
    QString("[%1, %2:%3]")                                                      \
    .arg(__PRETTY_FUNCTION__, __FILE__, QString::number(__LINE__)), "")             \

#define NEW_INTERNAL_EXCEPTION_EV(errorDesc, eventId)                           \
    new BfApiNgException((errorDesc),                                           \
    QString("[%1, %2:%3]")                                                      \
    .arg(__PRETTY_FUNCTION__, __FILE__, QString::number(__LINE__)),             \
    (eventId))                                                                   \


class BfApiNgException {
public:
  BfApiNgException(int code,
                   QString message,
                   QString errorDetails,
                   QString errorCode,
                   QString requestUUID,
                   QString trace,
                   QString eventIdTag) :
    m_errorType(API_NG_ERR), m_errorDesc(""),
    m_apiNgCode(code), m_apiNgMessage(message),
    m_apiNgErrorDetails(errorDetails), m_apiNgErrorCode(errorCode),
    m_apiNgRequestUUID(requestUUID), m_trace(trace),
    m_eventIdTag(eventIdTag)
  {
      qDebug() << "BfApiNgException()";
  }

  BfApiNgException(QString errorDesc, QString trace,
                   QString eventIdTag) :
    m_errorType(INTERNAL_ERR), m_errorDesc(errorDesc),
    m_apiNgCode(0), m_apiNgMessage(""),
    m_apiNgErrorDetails(""), m_apiNgErrorCode(""),
    m_apiNgRequestUUID(""), m_trace(trace),
    m_eventIdTag(eventIdTag) {

  }

  QString toString() {
    if (m_errorType == INTERNAL_ERR) {
      return QString("BfApiNgException(INTERNAL_ERR, errorDesc= %1, trace= %2)").arg(m_errorDesc, m_trace);
    }
    return QString("BfApiNgException(API_NG_ERR, code= %1, message= %2, errorDetails= %3, errorCode= %4, requestUUID= %5, trace= %6")
        .arg(QString::number(m_apiNgCode), m_apiNgMessage, m_apiNgErrorDetails, m_apiNgErrorCode, m_apiNgRequestUUID, m_trace);
  }

public:
  enum ErrorType {API_NG_ERR, INTERNAL_ERR};

  ErrorType m_errorType;

  // For internal
  QString m_errorDesc;

  // For ApiNg Error
  int m_apiNgCode;
  QString m_apiNgMessage;

  QString m_apiNgErrorDetails;
  QString m_apiNgErrorCode;
  QString m_apiNgRequestUUID;

  QString m_trace;

  // MORE
  QString m_eventIdTag;
};

#endif // APINGEXCEPTION

