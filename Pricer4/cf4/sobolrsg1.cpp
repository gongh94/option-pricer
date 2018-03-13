#include "sobolrsg1.h"
#include "sobol.hpp"

RandomSobol::RandomSobol(unsigned long Dimensionality, int Seed_)
	: RandomBase(Dimensionality),
	Seed(Seed_),
	InitialSeed(Seed_) {}

RandomBase* RandomSobol::clone() const
{
	return new RandomSobol(*this);
}


void RandomSobol::GetUniforms(MJArray& variates)
{
	// 1-dimensional sobol sequence
	double* sobol_dataset = i8_sobol_generate(1, GetDimensionality(), Seed);

	for (unsigned long j = 0; j < GetDimensionality(); j++)
		variates[j] = sobol_dataset[j];

	delete[] sobol_dataset;

}

void RandomSobol::Skip(unsigned long numberOfPaths)
{
	MJArray tmp(GetDimensionality());
	for (unsigned long j = 0; j < numberOfPaths; j++)
		GetUniforms(tmp);
}

void RandomSobol::SetSeed(unsigned long seed)
{
	//InitialSeed = Seed;
	Seed = seed;
}

void RandomSobol::Reset()
{
	Seed = InitialSeed;
}

void RandomSobol::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBase::ResetDimensionality(NewDimensionality);
	Seed = InitialSeed;
}