#ifndef BFCURRENTORDERS_H
#define BFCURRENTORDERS_H

#include <list>

#include <QString>

#include "bfenums/bfexecutionreportstatus.h"
#include "bfenums/bfexecutionreporterrorcode.h"
#include "bfenums/bforderstatus.h"

#include "bftypes/bfplaceinstructionreport.h"

class BfCurrentOrder {
public:
  BfCurrentOrder()
  {
  }

  /*
  QString toStr() const {
    QString piReports = "{";
    for (std::list<BfPlaceInstructionReport>::const_iterator it =
         m_instructionReports.begin(); it != m_instructionReports.end(); it++) {
      piReports += it->toStr() + ", ";
    }
    piReports += "}";
    return QString("BfPlaceExecutionReport(%1, %2, %3, %4")
        .arg(BfExecutionReportStatus::toStr(m_status),
             BfExecutionErrorReportCode::toStr(m_errorCode),
             m_marketId,
             piReports);
  }
  */
  /*
"{\"jsonrpc\":\"2.0\",\
"result\":
{\"currentOrders\":
[{\"betId\":\"77172245652\",
 \"marketId\":\"1.127665149\",
 \"selectionId\":47972,
 \"handicap\":0.0,
 \"priceSize\":
   {\"price\":2.06,
    \"size\":228.57},
 \"bspLiability\":0.0,
 \"side\":\"LAY\",
 \"status\":\"EXECUTION_COMPLETE\",
 \"persistenceType\":\"LAPSE\",
 \"orderType\":\"LIMIT\",
 \"placedDate\":\"2016-10-17T13:23:37.000Z\",
 \"matchedDate\":\"2016-10-17T13:23:37.000Z\",
 \"averagePriceMatched\":2.06,
 \"sizeMatched\":228.57,
 \"sizeRemaining\":0.0,
 \"sizeLapsed\":0.0,
 \"sizeCancelled\":0.0,
 \"sizeVoided\":0.0,
 \"regulatorCode\":\"MALTA LOTTERIES AND GAMBLING AUTHORITY\"}
],
\"moreAvailable\":false},\"id\":1}"
   * */

  QString m_betId;
  QString m_marketId;
  qint64 m_selectionId;
  double m_handicap;
  BfSide::Enum m_side;
  BfOrderStatus::Enum m_status;
  BfPersistenceType::Enum m_persistenceType;
  BfOrderType::Enum m_orderType;
  QDateTime m_placeDate;
  QDateTime m_matchedDate;
  double m_averagePriceMatched;
  double m_sizeMatched;
};

#endif // BFCURRENTORDERS_H

