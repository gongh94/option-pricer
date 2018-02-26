#ifndef FISHMAN_H
#define FISHMAN_H

#include <stdio.h>
#include "RandomBase.h"
#include "ParkMiller.h"

class RandomFishman : public RandomParkMiller
{
public:
	RandomFishman(unsigned long Dimensionality, unsigned long Seed = 1);

	virtual void GetGaussians(MJArray& variates);

private:
	RandomParkMiller InnerGenerator;
};
#endif