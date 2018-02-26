#ifndef SIMPLEMC_H
#define SIMPLEMC_H

#include "Vanilla3.h"
#include "Parameters.h"
#include "RandomBase.h"
#include "MCStatistics.h"

void SimpleMonteCarlo6(const VanillaOption& TheOption,
	double Spot,
	const Parameters& Vol,
	const Parameters& r,
	unsigned long NumberOfPaths,
	StatisticsMC& gatherer,
	RandomBase& generator);

#endif

