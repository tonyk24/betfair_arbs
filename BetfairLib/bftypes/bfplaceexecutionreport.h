#ifndef BFPLACEEXECUTIONREPORT_H
#define BFPLACEEXECUTIONREPORT_H

#include <list>

#include <QString>

#include "bfenums/bfexecutionreportstatus.h"
#include "bfenums/bfexecutionreporterrorcode.h"

#include "bftypes/bfplaceinstructionreport.h"

class BfPlaceExecutionReport {
public:
  BfPlaceExecutionReport() :
    m_errorCode(BfExecutionErrorReportCode::NONE),
    m_marketId("")
  {
  }

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

  BfExecutionReportStatus::Enum m_status;
  BfExecutionErrorReportCode::Enum m_errorCode;
  QString m_marketId;

  std::list<BfPlaceInstructionReport> m_instructionReports;
};

#endif // BFPLACEEXECUTIONREPORT_H

