#ifndef BFPPRICESIMLAYSIZE
#define BFPPRICESIMLAYSIZE

class BfPriceSimLaySize
{
public:
  BfPriceSimLaySize (QString selectionName,
                     double bfPrice,
                     double bfSimLaySize) :
    m_SelectionName(selectionName),
    m_bfPrice(bfPrice),
    m_bfSimLaySize(bfSimLaySize)
  {}


  QString m_SelectionName;
  double m_bfPrice;
  double m_bfSimLaySize;
};

#endif // BFPPRICESIMLAYSIZE

