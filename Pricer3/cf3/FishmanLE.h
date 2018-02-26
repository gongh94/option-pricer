#ifndef FISHMANLE_H
#define FISHMANLE_H

#include <stdio.h>
#include "RandomBase.h"
#include "LEcuyer.h"

class RandomFishmanLE : public RandomLEcuyer
{
public:
	RandomFishmanLE(unsigned long Dimensionality, unsigned long Seed = 1);

	virtual void GetGaussians(MJArray& variates);

private:
	RandomLEcuyer InnerGenerator;
};
#endif