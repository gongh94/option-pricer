#include "EulerMC.h"
#include "Random1.h"
#include <cmath>

#include <iostream>

using namespace std;

double EulerMonteCarlo(const PayOff& thePayOff,
	double Expiry,
	double Spot,
	double Vol,
	double r,
	double d,
	double NumberofSteps,
	unsigned long NumberOfPaths)
{

	double lengthOfStep = Expiry / NumberofSteps;
	double variance = Vol * Vol* lengthOfStep;
	double rootVariance = sqrt(variance);

	double thisSpot;
	double runningSum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		thisSpot = Spot;

		for (unsigned int i = 0; i < NumberofSteps; i++) {
			thisSpot += thisSpot * (r - d) * lengthOfStep + thisSpot * rootVariance * GetOneGaussianByBoxMuller();//!
		}

		double thisPayOff = thePayOff(thisSpot);
		runningSum += thisPayOff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
	
}