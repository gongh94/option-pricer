#ifndef LOGEULERMC_H
#define LOGEULERMC_H

#include "PayOff.h"

double LogEulerMonteCarlo(const PayOff& thePayOff,
	double Expiry,
	double Spot,
	double Vol,
	double r,
	double d,
	double NumberOfSteps,
	unsigned long NumberOfPaths);



#endif