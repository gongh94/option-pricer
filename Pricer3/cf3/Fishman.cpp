#include "Fishman.h"
#include <cmath>

RandomFishman::RandomFishman(unsigned long Dimensionality, unsigned long Seed)
	:RandomParkMiller(Dimensionality, Seed),
	InnerGenerator(3) {

}

void RandomFishman::GetGaussians(MJArray& variates) {

	MJArray U(3); //generate U1, U2, U3

	double x;

	for (unsigned long i = 0; i < RandomBase::GetDimensionality(); i++)
	{
		do {
			InnerGenerator.GetUniforms(U);

			x = -log(U[0]);

		} while (U[1] > exp(-0.5 * (abs(x) - 1) * (abs(x) - 1)));

		if (U[2] < 0.5) {
			x = -x;
		}

		variates[i] = x;
	}

}



