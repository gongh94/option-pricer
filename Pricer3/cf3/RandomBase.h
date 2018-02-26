#ifndef RANDOMBASE_H
#define RANDOMBASE_H

#include "Arrays.h"

class RandomBase
{
public:

    RandomBase(unsigned long Dimensionality);

    inline unsigned long GetDimensionality() const;

    virtual RandomBase* clone() const=0;
    virtual void GetUniforms(MJArray& variates) = 0;
    virtual void Skip(unsigned long numberOfPaths)=0;
	//virtual void SetSeed(unsigned long Seed); // in some cases, we may need multiple numbers
												// to initiate a random number generator
    virtual void Reset()=0;

	virtual void GetGaussians(MJArray& variates);

    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

    unsigned long Dimensionality;

};

unsigned long RandomBase::GetDimensionality() const
{
    return Dimensionality;
}

#endif

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Modified by Hangfeng Gong 2018
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

