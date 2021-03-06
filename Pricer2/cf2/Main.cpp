#include "Random1.h"
#include "Normals.h"
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

#include "ClosedForm.h"
#include "MonteCarlo.h"
#include "AntitheticMC.h"
#include "ControlMCr.h"


int main()
{

	double Expiry = 1;
	double Strike = 110;
	double Spot = 100;
	double Vol = 0.3;
	double r = 0.05;
	double d = 0.02;
	double OutBarrier = 120;
	unsigned long NumberOfPaths = 10000;
	double TimeSteps = 252;

	
	// (a) Use the closed-form formula to compute the price for a European-style call
	//     option with an up-and-out barrier.
	ClosedForm(Expiry,
		Strike,
		Spot,
		Vol,
		r, 
		d,
		OutBarrier,
		NumberOfPaths);


	// (b) Use Monte Carlo simulation to compute the prices for a European-styple call
	//     with an up-and-out barrier, the standart error, and the computation time.
	MonteCarlo(Expiry,
		Strike,
		Spot,
		Vol,
		r, 
		d,
		OutBarrier,
		NumberOfPaths,
		TimeSteps);


	// (c) Use Monte Carlo simulation with antithetic variance reduction to compute the
	//     prices for a European-style call with an up-and-out barrier, the standard error,
	//     and the computation time.
	AntitheticMC(Expiry,
		Strike,
		Spot,
		Vol,
		r, 
		d,
		OutBarrier,
		NumberOfPaths,
		TimeSteps);
		
	

	// (d) Use Monte Carlo simulation with vanilla option control variates(with the same 
	//     Strikes) to compute the prices for a European-style call with an up-and-out barrier,
	//     the standard error, and the computation time.
	ControlMC(Expiry,
		Strike,
		Spot,
		Vol,
		r, 
		d,
		OutBarrier,
		NumberOfPaths,
		TimeSteps);
		
	return 0;
}
