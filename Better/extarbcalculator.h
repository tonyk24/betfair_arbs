#ifndef EXTARBCALCULATOR_H
#define EXTARBCALCULATOR_H

#include <map>
#include <list>
#include <utility>

#include <QString>
#include <QObject>
#include <QDebug>

#include "bftypes/bfevent.h"

#include "models/currentbetsmodellisttype.h"

using namespace BfLib;

class ExtArbCalculator
{
public:
  ExtArbCalculator();
  static bool chooseBets(const BfEvent &event,
                  std::vector<CurrentBetsModelListType> &data,
                  double bfMaxExposure);
};

#endif // EXTARBCALCULATOR_H
