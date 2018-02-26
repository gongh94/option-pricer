#include "BoxMullerLE.h"
#include <cmath>

RandomBoxMullerLE::RandomBoxMullerLE(unsigned long Dimensionality, unsigned long Seed)
	:RandomLEcuyer(Dimensionality, Seed),
	InnerGenerator(2) {

}

void RandomBoxMullerLE::GetGaussians(MJArray& variates) {

	MJArray V(2); // generate V1, V2

	double x;
	double y;
	double sizeSquared;

	for (unsigned long i = 0; i < RandomBase::GetDimensionality(); i++)
	{
		do {
			InnerGenerator.GetUniforms(V);
			x = V[0] * 2.0 - 1;
			y = V[1] * 2.0 - 1;
			sizeSquared = x * x + y * y;

		} while (sizeSquared >= 1.0);


		variates[i] = x * sqrt(-2 * log(sizeSquared) / sizeSquared);
	}

}


