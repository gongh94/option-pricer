
#include "Random1.h"

//#include "LogEulerMC.h"
//#include "EulerMC.h"
#include "MilsteinMC.h"

#include <iostream>
#include <cmath>

using namespace std;

int main() {

	PayOff callPayOff(110, PayOff::call);
	PayOff putPayOff(110, PayOff::put);

	/*
	double resultCall2 = EulerMonteCarlo(callPayOff,
		1,
		100,
		1,
		0.05,
		0.02,
		252,
		10000);

	double resultPut2 = EulerMonteCarlo(putPayOff,
		1,
		100,
		1,
		0.05,
		0.02,
		252,
		10000);

	cout << "\nOption Price using Euler numerical solution of SDE for spot:\n";
	cout << "the prices are " << resultCall2 << "  for the call and "
		<< resultPut2 << " for the put\n";
		*/

	/*
	double resultCall3 = LogEulerMonteCarlo(callPayOff,
		1,
		100,
		1,
		0.05,
		0.02,
		252,
		10000);

	double resultPut3 = LogEulerMonteCarlo(putPayOff,
		1,
		100,
		1,
		0.05,
		0.02,
		252,
		10000);

	cout << "\nOption Price using Euler numerical solution of SDE for log spot:\n";
	cout << "the prices are " << resultCall3 << "  for the call and "
		<< resultPut3 << " for the put\n";
		*/

	double resultCall4 = MilsteinMonteCarlo(callPayOff,
		1,
		100,
		1,
		0.05,
		0.02,
		252,
		10000);

	double resultPut4 = MilsteinMonteCarlo(putPayOff,
		1,
		100,
		1,
		0.05,
		0.02,
		252,
		10000);

	cout << "\nOption Price using Milstein numerical solution of SDE for log spot:\n";
	cout << "the prices are " << resultCall4 << "  for the call and "
		<< resultPut4 << " for the put\n";

}