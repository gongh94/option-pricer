
#include "Random1.h"

#include "BlackScholesFormulas.h"
#include "SimpleMC.h"
#include "EulerMC.h"
#include "LogEulerMC.h"
#include "MilsteinMC.h"

#include <iostream>
#include <cmath>

using namespace std;

int main()
{

	double Expiry = 1;
	double Strike = 110;
	double Spot = 100;
	double Vol = 0.3;
	double r = 0.05;
	double d = 0.02; //dividend yield
	double NumberOfSteps = 252;
	unsigned long NumberOfPaths = 10000;

	/*
	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nEnter strike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nd\n";
	cin >> d;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;
	*/

	PayOff callPayOff(Strike, PayOff::call);
	//PayOff putPayOff(Strike, PayOff::put);
	
	// Option price using closed-form formula

	double resultCall0 = BlackScholesCall(Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry);
	/*
	double resultPut0 = BlackScholesPut(Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry);*/

	cout << "\nOption Price using closed-form formula = "<<resultCall0<<"\n";
	
	/*cout << "the prices are " << resultCall0 << "  for the call and "
		<< resultPut0 << " for the put\n";*/

	// Option price using single-step exact SDE solution

	double resultCall1 = SimpleMonteCarlo(callPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		d,
		NumberOfPaths);

	/*
	double resultPut1 = SimpleMonteCarlo(putPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		d,
		NumberOfPaths);
		*/

	cout << "\nOption Price using single-step exact SDE solution = "<<resultCall1<<"\n";
	
	/*cout << "the prices are " << resultCall1 << "  for the call and "
		<< resultPut1 << " for the put\n";*/
		

	// Option price using Euler numerical solution of SDE for spot

	double resultCall2 = EulerMonteCarlo(callPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		d,
		NumberOfSteps,
		NumberOfPaths);
	/*
	double resultPut2 = EulerMonteCarlo(putPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		d,
		NumberOfSteps,
		NumberOfPaths);
		*/

	cout << "\nOption Price using Euler numerical solution of SDE for spot = "<<resultCall2<<"\n";
	/*cout << "the prices are " << resultCall2 << "  for the call and "
		<< resultPut2 << " for the put\n";*/
	
	// Option price using Euler numerical solution of SDE for log spot

	double resultCall3 = LogEulerMonteCarlo(callPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		d,
		NumberOfSteps,
		NumberOfPaths);
	/*
	double resultPut3 = LogEulerMonteCarlo(putPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		d,
		NumberOfSteps,
		NumberOfPaths);*/

	cout << "\nOption Price using Euler numerical solution of SDE for log spot = "<<resultCall3<<"\n";
	
	/*cout << "the prices are " << resultCall3 << "  for the call and "
		<< resultPut3 << " for the put\n";*/

	// Option price using Milstein numerical solution of SDE for spot

	double resultCall4 = MilsteinMonteCarlo(callPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		d,
		NumberOfSteps,
		NumberOfPaths);

	/*
	double resultPut4 = MilsteinMonteCarlo(putPayOff,
		Expiry,
		Spot,
		Vol,
		r,
		d,
		NumberOfSteps,
		NumberOfPaths);
		*/

	cout << "\nOption Price using Milstein numerical solution of SDE for spot = " <<resultCall4<<"\n";
	
		/*cout << "the prices are " << resultCall4 << "  for the call and "
		<< resultPut4 << " for the put\n";*/

	return 0;
}
