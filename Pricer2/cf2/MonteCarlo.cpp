#include "MonteCarlo.h"

void MonteCarlo(double Expiry,
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
	double variance = Vol * Vol* h;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double thisSpot = Spot;
	double runningSum = 0;
	double* payoff = new double[NumberOfPaths] ();

	double moveFactor = exp((r - d)*h + itoCorrection);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = Spot;
		bool isOut = false;

		for (int j = 0; j < TimeSteps; j++)
		{
			double thisGaussian = GetOneGaussianByBoxMuller();

			thisSpot = thisSpot* moveFactor * exp(rootVariance*thisGaussian);
			
			if (thisSpot > OutBarrier)
			{
				isOut = true;
				break;
			}
		}

		double thisPayoff = 0;

		if (!isOut)
		{
			thisPayoff = thisSpot - Strike;
			thisPayoff = thisPayoff >0 ? thisPayoff : 0;
			thisPayoff *= exp(-r * Expiry);
			
		}
		else {
			thisPayoff = 0;
		}

		payoff[i] = thisPayoff;
		runningSum += thisPayoff;

	}

	double mean = runningSum / static_cast<double>(NumberOfPaths);

	double square_sum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		square_sum += (payoff[i] - mean)*(payoff[i] - mean);
	}

	double std_error = sqrt(square_sum / static_cast<double>(NumberOfPaths));

	cout << "Monte Carlo barrier option price = " << mean << ", ";
	cout << "std error = " << std_error << ", ";
	cout << "run time = " << (double)(clock() - tStart) / CLOCKS_PER_SEC<<"s\n\n";

	delete[] payoff;
} 