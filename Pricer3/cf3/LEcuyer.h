
#ifndef LECUYER_H
#define LECUYER_H

#include "RandomBase.h"
#include <stdio.h>

class LEcuyer
{
public:

	LEcuyer(long x10 = 1, long x11 = 2, long x12 = 3, long x20 = 5, long x21 = 7, long x22 = 11);
	long GetOneRandomInteger();
	void SetSeed(long x10_, long x11_, long x12_, long x20_, long x21_, long x22_);

	static unsigned long Max();
	static unsigned long Min();

private:

	long x10, x11, x12;
	long x20, x21, x22;

};

class RandomLEcuyer : public RandomBase
{
public:

	RandomLEcuyer(unsigned long Dimensionality, unsigned long x10_ = 1, unsigned long x11_ = 2, unsigned long x12_ = 3, unsigned long x20_ = 5, unsigned long x21_ = 7, unsigned long x22_ = 11);

	virtual RandomBase* clone() const;
	virtual void GetUniforms(MJArray& variates);
	virtual void Skip(unsigned long numberOfPaths);
	virtual void SetSeed(unsigned long x10, unsigned long x11, unsigned long x12, unsigned long x20, unsigned long x21, unsigned long x22);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

	LEcuyer InnerGenerator;
	unsigned long Initialx10;
	unsigned long Initialx11;
	unsigned long Initialx12;
	unsigned long Initialx20;
	unsigned long Initialx21;
	unsigned long Initialx22;
	double Reciprocal;



};

#endif // 