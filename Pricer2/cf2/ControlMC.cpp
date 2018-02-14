#include "ControlMCr.h"

void ControlMC(double Expiry,
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

	double vanillaVariance = Vol * Vol* Expiry;
	double rootVanillaVariance = sqrt(vanillaVariance);
	double vanillaItoCorrection = -0.5*vanillaVariance;

	double thisSpot = Spot;
	double vThisSpot = 0;

	double runningSum = 0;
	double vRunningSum = 0;

	double* payoff = new double[NumberOfPaths]();
	double* vPayoff = new double[NumberOfPaths]();

	// compute vanilla call price for each path and their mean
	

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double vanillaGaussian = GetOneGaussianByBoxMuller();
		vThisSpot = Spot * exp((r - d)*Expiry + rootVanillaVariance * vanillaGaussian);
		
		double vanillaPayoff = vThisSpot - Strike;
		vanillaPayoff = vanillaPayoff > 0 ? vanillaPayoff : 0;
		vanillaPayoff *= exp(-r * Expiry);
		
		vPayoff[i] = vanillaPayoff;
		vRunningSum += vanillaPayoff;
	}

	double vanillaMean = vRunningSum / static_cast<double>(NumberOfPaths);

	// compute barrier option price for each path and their mean

	double moveFactor = exp((r - d)*h + itoCorrection);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = Spot;
		bool isOut = false;

		for (int j = 0; j < TimeSteps; j++)
		{
			double thisGaussian = GetOneGaussianByBoxMuller();

			thisSpot = thisSpot * moveFactor * exp(rootVariance*thisGaussian);

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

	double bNumerator = 0;
	double bDenominator = 0;

	for (unsigned long i = 0; i < NumberOfPaths*0.1; i++)
	{
		bNumerator += (vPayoff[i] - vanillaMean)*(payoff[i] - mean);
		bDenominator += (vPayoff[i] - vanillaMean)*(vPayoff[i] - vanillaMean);
	}

	double b_hat = bNumerator/bDenominator;

	double cve = 0; // control variate estimator

	for (unsigned long i = NumberOfPaths*0.1; i < NumberOfPaths; i++)
	{
		cve += payoff[i] - b_hat * (vPayoff[i] - vanillaMean);
	}

	cve = cve / NumberOfPaths*0.9;

	double cve_SSD = 0, rou = 0, X_SSD = 0; // sum of squared deviation

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		
		rou += (vPayoff[i] - vanillaMean)*(payoff[i] - mean);
		X_SSD += (vPayoff[i] - vanillaMean)*(vPayoff[i] - vanillaMean);

		cve_SSD += (payoff[i] - cve)*(payoff[i] - cve);
	}

	rou = rou / sqrt(X_SSD*X_SSD);

	//std_error = sample SD / sqrt(sizeOfSample)
	double std_error = sqrt(cve_SSD/(NumberOfPaths-1))/sqrt(NumberOfPaths);

	cout << "Control variates barrier option price = " << cve << ", ";
	cout << "std error = " << std_error << ", ";
	cout << "run time = " << (double)(clock() - tStart) / CLOCKS_PER_SEC <<"s,\n";
	cout << "  control coefficient is : " << b_hat << ", " << "correlation is: " << rou <<"\n\n";

	delete[] payoff;
	delete[] vPayoff;
} 