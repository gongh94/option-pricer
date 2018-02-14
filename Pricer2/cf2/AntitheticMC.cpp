#include "AntitheticMC.h"

void AntitheticMC(double Expiry,
	double Strike,
	double Spot,
	double Vol,
	double r,
	double d,
	double OutBarrier,
	unsigned long NumberOfPaths,
	double TimeSteps)
{
	clock_t tStart = clock();

	double h = Expiry / TimeSteps;
	double variance = Vol * Vol*h;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double thisSpot1, thisSpot2;
	double runningSum = 0;
	double* payoff = new double[NumberOfPaths]();
	double moveFactor = exp((r - d)*h + itoCorrection);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		thisSpot1 = Spot;
		thisSpot2 = Spot;

		bool isOut1 = false, isOut2 = false;

		for (int j = 0; j < TimeSteps; j++)
		{
			double thisGaussian1 = GetOneGaussianByBoxMuller();
			double thisGaussian2 = -thisGaussian1;

			if (!isOut1) thisSpot1 = thisSpot1 * moveFactor * exp(rootVariance*thisGaussian1);

			if (!isOut2) thisSpot2 = thisSpot2 * moveFactor * exp(rootVariance*thisGaussian2);

			if (thisSpot1 > OutBarrier) isOut1 = true;

			if (thisSpot2 > OutBarrier) isOut2 = true;
			
		}

		double thisPayoff1 = thisSpot1 - Strike;

		if (!isOut1) {
			thisPayoff1 = thisPayoff1 > 0 ? thisPayoff1 : 0;
			thisPayoff1 *= exp(-r * Expiry);
		}
		else {
			thisPayoff1 = 0;
		}

		double thisPayoff2 = thisSpot2 - Strike;

		if (!isOut2) {
			thisPayoff2 = thisPayoff2 > 0 ? thisPayoff2 : 0;
			thisPayoff2 *= exp(-r * Expiry);
		}
		else {
			thisPayoff2 = 0;
		}

		double thisPayoff = (thisPayoff1 + thisPayoff2) / 2;
		payoff[i] = thisPayoff;
		runningSum += thisPayoff;
	
	}

	double mean = runningSum / static_cast<double>(NumberOfPaths);

	double square_sum = 0;
	
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		square_sum += (payoff[i] - mean)*(payoff[i] - mean);
	}

	//std_error = sample SD / sqrt(sizeOfSample)
	double std_error = sqrt(square_sum / NumberOfPaths)/sqrt(NumberOfPaths);

	cout << "Antithetic variates barrier option price = " << mean << ", ";
	cout << "std error = " << std_error << ", ";
	cout << "run time = " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s\n\n";

	delete[] payoff;
} 