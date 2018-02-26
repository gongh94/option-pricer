#ifndef BOXMULLERLE_H
#define BOXMULLERLE_H

#include <stdio.h>
#include "RandomBase.h"
#include "LEcuyer.h"

class RandomBoxMullerLE : public RandomLEcuyer
{
public:
	RandomBoxMullerLE(unsigned long Dimensionality, unsigned long Seed = 1);

	virtual void GetGaussians(MJArray& variates);

private:
	RandomLEcuyer InnerGenerator;
};
#endif