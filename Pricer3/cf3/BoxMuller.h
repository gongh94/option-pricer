#ifndef BOXMULLER_H
#define BOXMULLER_H

#include <stdio.h>
#include "RandomBase.h"
#include "ParkMiller.h"

class RandomBoxMuller : public RandomParkMiller
{
public:
	RandomBoxMuller(unsigned long Dimensionality, unsigned long Seed = 1);

	virtual void GetGaussians(MJArray& variates);

private:
	RandomParkMiller InnerGenerator;
};
#endif