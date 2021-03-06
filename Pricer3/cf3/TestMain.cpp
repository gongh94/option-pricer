// cf3.cpp : Defines the entry point for the console application.
//
#include "ParkMiller.h"
#include "LEcuyer.h"
#include <iostream>

using namespace std;

int main()
{
	RandomParkMiller generator(1);
	generator.SelectGaussianAlgorithm(2);
	
	/*
	for (unsigned int i = 0; i < 10; i++)
	{
		MJArray VariateArray(1);
		generator.GetUniforms(VariateArray);
		cout << VariateArray[0] <<", ";
	}*/

	/*
	MJArray UniTwo(2);
	double v1;
	double v2;
	double sizeSquared;

	unsigned int i = 0;

	do {
		generator.GetUniforms(UniTwo,2);
		v1 = UniTwo[0] * 2 - 1;
		v2 = UniTwo[1] * 2 - 1;
		sizeSquared = v1 * v1 + v2 * v2;
		i++;
	} while (sizeSquared >= 1 && i < 10);

	*/
	

	
	generator.SelectGaussianAlgorithm(2);

	for (unsigned int i = 0; i < 10; i++)
	{
		
		MJArray VariateArray(1);
		generator.GetGaussians(VariateArray);
		cout << VariateArray[0] << ", ";
	}
	

	/*
	for (unsigned i = 0; i < 20; i++)
		cout << r.GetOneRandomInteger() << ", ";

	cout << "\n\n";

	for (unsigned i = 0; i < 20; i++)
		cout << p.GetOneRandomInteger() << ", ";
		*/

    return 0;
}

