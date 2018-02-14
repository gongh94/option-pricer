#include "LogEulerMC.h"
#include "Random1.h"
#include <cmath>

using namespace std;

double LogEulerMonteCarlo(const PayOff& thePayOff,
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
	//double itoCorrection = -0.5*variance;


	double lengthOfStep = Expiry / NumberofSteps;
	double variance = Vol * Vol * lengthOfStep;
	double rootVariance = sqrt(variance);

	double itoCorrection = -0.5 * Vol * Vol;

	double thisLogSpot;
	double runningSum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		thisLogSpot = log(Spot);

		for (unsigned int i = 0; i < NumberofSteps; i++) {
			thisLogSpot += (r - d + itoCorrection) * lengthOfStep + rootVariance * GetOneGaussianByBoxMuller();//!
		}

		double thisPayOff = thePayOff(exp(thisLogSpot));
		runningSum += thisPayOff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;

}