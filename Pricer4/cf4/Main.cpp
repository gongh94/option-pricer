#include"ParkMiller.h"
#include"sobolrsg1.h"
#include"sobol.hpp"
#include"Normals.h"
#include<iostream>
#include<cmath>
#include<algorithm>
#include<stdlib.h>
#include<vector>

#include "BlackScholesFormulas.h"

// Quasi Monte Carlo: 
// used to price European vanilla options
// accept a quasi-random number generator
double QuasiMC(double spot, double vol, double r, double expiry,
	unsigned long npoints, double strike, RandomBase& qrsg);

// Simple Monte Carlo:
// used to price European vanilla options
// accept a pseudo-random number generator
double SimpleMC(double spot, double vol, double r, unsigned long npaths, double expiry,
	double strike, RandomBase& prsg);

// Simple Monte Carlo with antithetic
// used to price European vanilla options
// accept a pseudo-random number generator
double AntitheticMC(double spot, double vol, double r, unsigned long npaths, double expiry,
	double strike, RandomBase& prsg);


int main()
{

	double Expiry = 1;
	double Strike = 110;
	double Spot = 100;
	double Vol = 0.3;
	double r = 0.05;
	unsigned long NumberOfPaths = 10000;

	unsigned long NumberOfPoints = 1000; // size of sobol sequence

	double price1 = BlackScholesCall(Spot, Strike, r, 0, Vol, Expiry);
	std::cout << "Closed-form vanilla call option price = " << price1 << "\n\n";

	RandomParkMiller PMrsg(1);  

	double price2 = SimpleMC(Spot, Vol, r, NumberOfPaths, Expiry, Strike, PMrsg);
	std::cout << "MC European call price with Park-Miller uniforms = " << price2 << "\n\n";

	double price3 = AntitheticMC(Spot, Vol, r, NumberOfPaths, Expiry, Strike, PMrsg);
	std::cout << "MC European call price with Park-Miller uniforms and antithetics = " << price3 << "\n\n";

	// generate 1-dimensional Sobol sequence
	RandomSobol sobolrsg(NumberOfPoints, 5);

	double price4 = QuasiMC(Spot, Vol, r, Expiry, NumberOfPoints, Strike, sobolrsg);
	std::cout << "QMC European call price = " << price4 << "\n\n";


	return 0;
}


double QuasiMC(double spot, double vol, double r, double expiry,
	unsigned long npoints, double strike,  RandomBase& qrsg)
{

	double variance = vol * vol * expiry;
	double rootVariance = sqrt(variance);
	double ItoCorrection = - 0.5 * vol* vol;

	double S_0 = spot, S_T = spot;

	double runningSum = 0;
	double thisPayOff = 0;
	MJArray Gaussians(npoints);

	// Use the Euler numerical solution to dS(t) = S(t)*(r*dt + sigma*dW(t))
	qrsg.GetGaussians(Gaussians);

			for (unsigned int j = 0; j < npoints; j++)
			{
				S_T =  S_0 * exp( (r + ItoCorrection) * expiry + rootVariance * Gaussians[j]);
				thisPayOff = std::max(S_T - strike, 0.0);
				runningSum += thisPayOff;
			}

			double mean = runningSum / npoints;

	return mean * exp(-r * expiry);
} 


double SimpleMC(double spot, double vol, double r, unsigned long npaths, double expiry,
	double strike, RandomBase& prsg)
{
	MJArray VariateArray(1);
	prsg.ResetDimensionality(1);

	double variance = vol * vol * expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = spot * exp(r * expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;

	for (unsigned long i = 0; i < npaths; i++)
	{
		prsg.GetGaussians(VariateArray);
		thisSpot = movedSpot * exp(rootVariance*VariateArray[0]);
		double thisPayOff = std::max(thisSpot - strike, 0.0);
		runningSum += thisPayOff;
	}

	double mean = runningSum / npaths;
	mean *= exp(-r * expiry);
	return mean;
} 

double AntitheticMC(double spot, double vol, double r, unsigned long npaths, double expiry,
	double strike, RandomBase& prsg)
{
	double variance = vol * vol * expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot1 = spot * exp(r * expiry + itoCorrection);
	double movedSpot2 = spot * exp(r * expiry + itoCorrection);
	double thisSpot1, thisSpot2;
	double runningSum = 0;

	prsg.ResetDimensionality(1);
	MJArray VariateArray(1);

	for (unsigned long i = 0; i < npaths; i++)
	{

		prsg.GetGaussians(VariateArray);
		double thisGaussian = VariateArray[0];
		thisSpot1 = movedSpot1* exp(rootVariance * thisGaussian);
		thisSpot2 = movedSpot2 * exp(- rootVariance * thisGaussian);

		double thisPayOff = (std::max(thisSpot1 - strike, 0.0) + std::max(thisSpot2 - strike,0.0))/2;
		
		runningSum += thisPayOff;
		
	}


	double mean = runningSum / npaths;
	mean *= exp(-r * expiry);

	return mean;
} 