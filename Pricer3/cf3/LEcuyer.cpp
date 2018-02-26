#include "LEcuyer.h"
#include <cmath>
#include <iostream>

const long m1 = 2147483647;
// a11 = 0;
const long a12 = 63308;
const long a13 = -183326;

const long m2 = 2145483479;
const long a21 = 86098;
// a22 = 0;
const long a23 = -539608;

const long q12 = 33921;
const long q13 = 11714;
const long q21 = 24919;
const long q23 = 3976;

const long r12 = 12979;
const long r13 = 2883;
const long r21 = 7417;
const long r23 = 2071;

const long double k = 4.656612873077393e-10; // k = 1/(m+1)

// class LEcuyer

LEcuyer::LEcuyer(long x10_, long x11_, long x12_, long x20_, long x21_, long x22_):
	x10(x10_),
	x11(x11_),
	x12(x12_),
	x20(x20_),
	x21(x21_),
	x22(x22_)
{	
	if (x10 == 0)
		x10 = 1;

	if (x11 == 0)
		x11 = 2;
	
	if (x12 == 0)
		x12 = 3;
	
	if (x20 == 0)
		x20 = 5;
	
	if (x21 == 0)
		x21 = 7;
	
	if (x22 == 0)
		x22 = 11;
} 

void LEcuyer::SetSeed(long x10_, long x11_, long x12_, long x20_, long x21_, long x22_)
{
	x10 = x10_; 
	x11 = x11_; 
	x12 = x12_;
	x20 = x20_; 
	x21 = x21_;
	x22 = x22_;
	
	if (x10 == 0)
		x10 = 1;
	if (x11 == 0)
		x11 = 2;
	if (x12 == 0)
		x12 = 3;
	if (x20 == 0)
		x20 = 5;
	if (x21 == 0)
		x21 = 7;
	if (x22 == 0)
		x22 = 11;
}

long LEcuyer::GetOneRandomInteger()
{
	int h, p12, p13, p21, p23;
	
	//compute a12*x11 mod m1
	h = x11 / q12; 
	p12 = a12 * (x11 - h * q12) - h * r12;
	if (p12 < 0) 
		p12 += m1;
	
	//compute a13*x10 mod m1
	h = x10 / q13; 
	p13 = a13 * (x10 - h * q13) - h * r13;
	if (p13 < 0) 
		p13 += m1; 

	//compute a21*x22 mod m2
	h = x22 / q21; 
	p21 = a21 * (x22 - h * q21) - h * r21;
	if (p21 < 0) 
		p21 += m2; 

	//compute a23*x20 mod m2
	h = x20 / q23;
	p23 = a23 * (x20 - h * q23) - h * r23;
	if (p23 < 0)
		p23 += m2;

	//update x11 and x10
	x10 = x11; 
	x11 = x12; 

	//compute (p12+p13) mod m1 and update x12
	p12 -= m1;
	x12 = p12 + p13;
	if (x12 < 0) 
		x12 += m1; 

	//update x21 and x20
	x20 = x21; 
	x21 = x22; 
	
	//compute (p21 + p23) mod m2 and update x22
	p21 -= m2;
	x22 = p21 + p23;
	if (x22 < 0) 
		x22 += m2; 

	// compute x1 mod m1
	if (x12 < x22)
		return x12 - x22 + m1;
	else return x12 - x22;

}

unsigned long LEcuyer::Max()
{
	return m1 - 1;
}

unsigned long LEcuyer::Min()
{
	return 1;
}

// class RandomLEcuyer
RandomLEcuyer::RandomLEcuyer(unsigned long Dimensionality, unsigned long x10_, unsigned long x11_, unsigned long x12_, unsigned long x20_, unsigned long x21_, unsigned long x22_)
	: RandomBase(Dimensionality),
	InnerGenerator(x10_, x11_, x12_, x20_, x21_, x22_),
	Initialx10(x10_),
	Initialx11(x11_),
	Initialx12(x12_),
	Initialx20(x20_),
	Initialx21(x21_),
	Initialx22(x22_)
{
	Reciprocal = 1 / (1.0 + InnerGenerator.Max());
}


void RandomLEcuyer::SetSeed(unsigned long x10, unsigned long x11, unsigned long x12, unsigned long x20, unsigned long x21, unsigned long x22)
{
	Initialx10 = x10;
	Initialx11 = x11;
	Initialx12 = x12;
	Initialx20 = x20;
	Initialx21 = x21;
	Initialx22 = x22;
	InnerGenerator.SetSeed(x10, x11, x12, x20, x21, x22);
}

RandomBase* RandomLEcuyer::clone() const
{
	return new RandomLEcuyer(*this);
}


void RandomLEcuyer::GetUniforms(MJArray& variates)
{
	for (unsigned long j = 0; j < RandomLEcuyer::GetDimensionality(); j++) {
		variates[j] = InnerGenerator.GetOneRandomInteger()*Reciprocal;
	}
}


void RandomLEcuyer::Skip(unsigned long numberOfPaths)
{
	MJArray tmp(GetDimensionality());
	for (unsigned long j = 0; j < numberOfPaths; j++)
		GetUniforms(tmp);
}


void RandomLEcuyer::Reset()
{
	InnerGenerator.SetSeed(Initialx10, Initialx11, Initialx12, Initialx20, Initialx21, Initialx22);
}


void RandomLEcuyer::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBase::ResetDimensionality(NewDimensionality);
	InnerGenerator.SetSeed(Initialx10, Initialx11, Initialx12, Initialx20, Initialx21, Initialx22);
}