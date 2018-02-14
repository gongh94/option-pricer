#include "Random1.h"

#include "BlackScholesFormulas.h"
#include "SimpleMC.h"
#include "EulerMC.h"
#include "LogEulerMC.h"
#include "MilsteinMC.h"

#include <iostream>
#include <cmath>

using namespace std;

double log_sd(double*, unsigned int);

int main()
{

	double Expiry = 1;
	double Strike = 110;
	double Spot = 100;
	double Vol = 0.3;
	double r = 0.05;
	double d = 0.02; //dividend yield
	double NumberOfSteps = 252;
	unsigned long NumberOfPaths = 0;

	double prices[10] = {};

	PayOff callPayOff(Strike, PayOff::call);

	for (unsigned int j = 1000; j <= 8000; j *= 2)
	{
		NumberOfPaths = j;

		for (unsigned int i = 0; i < 10; i++)
		{

			srand(i + 10000);

			/*
			double resultCall1 = SimpleMonteCarlo(callPayOff,
				Expiry,
				Spot,
				Vol,
				r,
				d,
				NumberOfPaths);
				*/

			/*
			double resultCall2 = EulerMonteCarlo(callPayOff,
				Expiry,
				Spot,
				Vol,
				r,
				d,
				NumberOfSteps,
				NumberOfPaths);
				*/

			/*
			double resultCall3 = LogEulerMonteCarlo(callPayOff,
				Expiry,
				Spot,
				Vol,
				r,
				d,
				NumberOfSteps,
				NumberOfPaths);
				*/

			double resultCall4 = MilsteinMonteCarlo(callPayOff,
				Expiry,
				Spot,
				Vol,
				r,
				d,
				NumberOfSteps,
				NumberOfPaths);

			prices[i] = resultCall4;
		}

		cout << log_sd(prices, 10) << " ";

		//cout << log(static_cast<double>(NumberOfPaths)) << " ";
	}

	/*
	for (unsigned int i = 10; i < 10000; i += 1000)
	{
		NumberOfPaths = i;

		double resultCall2 = EulerMonteCarlo(callPayOff,
			Expiry,
			Spot,
			Vol,
			r,
			d,
			NumberOfSteps,
			NumberOfPaths);

		cout << "\nOption Price using Euler numerical solution of SDE for spot = " << resultCall2 << "\n";
	}

	for (unsigned int i = 10; i < 10000; i += 1000)
	{
		NumberOfPaths = i;

		double resultCall3 = LogEulerMonteCarlo(callPayOff,
			Expiry,
			Spot,
			Vol,
			r,
			d,
			NumberOfSteps,
			NumberOfPaths);

		cout << "\nOption Price using Euler numerical solution of SDE for log spot = " << resultCall3 << "\n";

	}

	for (unsigned int i = 10; i < 10000; i += 1000)
	{
		NumberOfPaths = i;

		double resultCall4 = MilsteinMonteCarlo(callPayOff,
			Expiry,
			Spot,
			Vol,
			r,
			d,
			NumberOfSteps,
			NumberOfPaths);

		cout << "\nOption Price using Milstein numerical solution of SDE for spot = " << resultCall4 << "\n";
	}

	*/
	return 0;
}

double log_sd(double* a, unsigned int size) {
	
	double sum = 0, ave = 0, d_square = 0, sd = 0;

	for (unsigned int i = 0; i < size; i++) {
		sum += a[i];
	}

	ave = sum / static_cast<double>(size);

	for (unsigned int i = 0; i < size; i++) {
		d_square += (a[i] - ave)*(a[i] - ave);
	}

	sd = sqrt(d_square/static_cast<double>(size));
	return log(sd);
}