#ifndef BFCANCELINSTRUCTIONREPORT_H
#define BFCANCELINSTRUCTIONREPORT_H

#include <QDateTime>

#include "bfenums/bfinstructionreportstatus.h"
#include "bfenums/bfinstructionreporterrorcode.h"

#include "bftypes/bfcancelinstruction.h"

class BfCancelInstructionReport {
public:
  BfCancelInstructionReport() :
    m_status(BfInstructionReportStatus::FAILURE),
          m_errorCode(BfInstructionReportErrorCode::NONE),
          m_instruction(BfCancelInstruction()),
          m_sizeCancelled(0.0),
          m_cancelledDate(QDateTime::currentDateTimeUtc()) {

  }

   QString toStr() const {
     return QString("CancelInstructionReport(%1 %2 %3)")
         .arg(BfInstructionReportStatus::toStr(m_status),
              BfInstructionReportErrorCode::toStr(m_errorCode),
              m_instruction.toStr());
   }

  BfInstructionReportStatus::Enum m_status;
  BfInstructionReportErrorCode::Enum m_errorCode;

  BfCancelInstruction m_instruction;
  double m_sizeCancelled;
  QDateTime m_cancelledDate;
};

#endif // BFCANCELINSTRUCTIONREPORT_H

