#include "MilsteinMC.h"
#include "Random1.h"
#include <cmath>

using namespace std;

double MilsteinMonteCarlo(const PayOff& thePayOff,
	double Expiry,
	double Spot,
	double Vol,
	double r,
	double d,
	double NumberofSteps,
	unsigned long NumberOfPaths)
{

	//double variance = Vol * Vol*Expiry;
	//double rootVariance = sqrt(variance);


	double lengthOfStep = Expiry / NumberofSteps;

	double thisSpot;
	double runningSum = 0;
	double deltaW = 0;


	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		thisSpot = Spot;

		for (unsigned int i = 0; i < NumberofSteps; i++) {

			deltaW = sqrt(lengthOfStep) * GetOneGaussianByBoxMuller();

			thisSpot += thisSpot * (r - d) * lengthOfStep + thisSpot * Vol * deltaW + 
				0.5 * thisSpot * Vol * Vol *(deltaW * deltaW - lengthOfStep);
		}

		double thisPayOff = thePayOff(thisSpot);
		runningSum += thisPayOff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;

}