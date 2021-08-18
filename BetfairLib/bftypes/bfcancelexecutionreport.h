#ifndef BFCANCELEXECUTIONREPORT_H
#define BFCANCELEXECUTIONREPORT_H

#include <list>

#include <QString>

#include "bfenums/bfexecutionreportstatus.h"
#include "bfenums/bfexecutionreporterrorcode.h"

#include "bftypes/bfcancelinstruction.h"
/*
 *
 * */

class BfCancelExecutionReport
{
public:
  QString m_customerRef;
  BfExecutionReportStatus::Enum m_status;
  BfExecutionErrorReportCode::Enum m_errorCode;
  QString m_marketId;

  std::list<BfCancelInstruction> m_instructionReports;

};

#endif // BFCANCELEXECUTIONREPORT_H

