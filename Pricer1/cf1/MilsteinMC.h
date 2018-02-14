#ifndef MILSTEINMC_H
#define MILSTEINMC_H

#include "PayOff.h"

double MilsteinMonteCarlo(const PayOff& thePayOff,
	double Expiry,
	double Spot,
	double Vol,
	double r,
	double d,
	double NumberOfSteps,
	unsigned long NumberOfPaths);



#endif