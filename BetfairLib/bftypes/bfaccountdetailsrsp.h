#ifndef BFACCOUNTDETAILSRSP_H
#define BFACCOUNTDETAILSRSP_H

#include <QString>

class BfAccountDetailsRsp {
public:
  BfAccountDetailsRsp()
    : m_currencyCode(""),
      m_firstName(""),
      m_lastName(""),
      m_localeCode(""),
      m_region(""),
      m_timezone(""),
      m_discountRate(0.0),
      m_pointsBalance(0),
      m_countryCode("")
  {

  }

  // Default user currency Code. See Currency Parameters for minimum bet sizes relating to each currency.
  QString m_currencyCode;

  // First Name
  QString m_firstName;

  // Last Name
  QString m_lastName;

  // Locale code
  QString m_localeCode;

  // Region based on users zip/postcode (ISO 3166-1 alpha-3 format). Defaults to GBR if zip/postcode cannot be identified.
  QString m_region;

  // User Time Zone.
  QString m_timezone;

  // User discount rate
  double m_discountRate;

  // The Betfair points balance
  int m_pointsBalance;

  // The customer's country of residence (ISO 2 Char format)
  QString m_countryCode;
};

#endif // BFACCOUNTDETAILSRSP_H

