#ifndef BFACCOUNTFUNDSRSP_H
#define BFACCOUNTFUNDSRSP_H

class BfAccountFundsRsp {
public:
  BfAccountFundsRsp() :
    m_availableToBetBalance(0.0),
    m_exposure(0.0),
    m_retainedCommission(0.0),
    m_exposureLimit(0.0),
    m_discountRate(0.0),
    m_pointsBalance(0)
  {}

  // Amount available to bet.
  double m_availableToBetBalance;
  // Current exposure.
  double m_exposure;
  // Sum of retained commission
  double m_retainedCommission;
  // Exposure limit
  double m_exposureLimit;
  // User Discount Rate
  double m_discountRate;
  // The Betfair points balance
  int m_pointsBalance;
};

#endif // BFACCOUNTFUNDSRSP_H

