#pragma once
#ifndef EULERMC_H
#define EULERMC_H

#include "PayOff.h"

double EulerMonteCarlo(const PayOff& thePayOff,
	double Expiry,
	double Spot,
	double Vol,
	double r,
	double d,
	double NumberOfSteps,
	unsigned long NumberOfPaths);



#endif