#ifndef BFPLACEINSTRUCTIONREPORT_H
#define BFPLACEINSTRUCTIONREPORT_H

#include <QString>
#include <QDateTime>
#include "bfenums/bfinstructionreportstatus.h"
#include "bfenums/bfinstructionreporterrorcode.h"

#include "bftypes/bfplaceinstruction.h"

class BfPlaceInstructionReport {
public:
  BfPlaceInstructionReport() :
    m_status(BfInstructionReportStatus::FAILURE),
          m_errorCode(BfInstructionReportErrorCode::NONE),
          m_betId(""),
          m_averagePriceMatched(0.0),
          m_sizeMatched(0.0),
          m_placeInstruction(BfPlaceInstruction()) {

  }

  BfPlaceInstructionReport(BfInstructionReportStatus::Enum status,
                           BfPlaceInstruction placeInstruction)
    : m_status(status),
      m_errorCode(BfInstructionReportErrorCode::NONE),
      m_betId(""),
      m_averagePriceMatched(0.0),
      m_sizeMatched(0.0),
      m_placeInstruction(placeInstruction)
  {
  }

   QString toStr() const {
     return QString("BfPlaceInstructionReport(%1 %2 %3)")
         .arg(BfInstructionReportStatus::toStr(m_status),
              BfInstructionReportErrorCode::toStr(m_errorCode),
              m_placeInstruction.toStr());
   }

  BfInstructionReportStatus::Enum m_status;
  BfInstructionReportErrorCode::Enum m_errorCode;

  QString m_betId;
  QDateTime m_placeDate;
  double m_averagePriceMatched;
  double m_sizeMatched;

  BfPlaceInstruction m_placeInstruction;
};

#endif // BFPLACEINSTRUCTIONREPORT_H

