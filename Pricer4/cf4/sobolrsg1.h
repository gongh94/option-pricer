#ifndef SOBOLRSG1_H
#define SOBOLRSG1_H

#include <stdio.h>
#include "Random2.h"
#include "sobol.hpp"


class RandomSobol : public RandomBase
{
public:

	RandomSobol(unsigned long Dimensionality, int Seed = 5);

	virtual RandomBase* clone() const;
	virtual void GetUniforms(MJArray& variates);
	virtual void Skip(unsigned long numberOfPaths);
	virtual void SetSeed(unsigned long seed);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

	int Seed;
	int InitialSeed;

};

#endif 
