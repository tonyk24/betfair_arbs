#ifndef BFCANCELINSTRUCTION_H
#define BFCANCELINSTRUCTION_H

#include <QString>

class BfCancelInstruction
{
public:
  BfCancelInstruction(QString betId) :
    m_betId(betId),
    m_sizeReduction(0.0)
  {
  }
  BfCancelInstruction() :
    m_betId(""),
    m_sizeReduction(0.0)
  {
  }

  QString toStr() const {
    return QString("BfCancelInstruction(%1 %2 %3)")
        .arg(m_betId,QString::number(m_sizeReduction));
  }

  QString m_betId;
  double m_sizeReduction;
};

#endif // BFCANCELINSTRUCTION_H
