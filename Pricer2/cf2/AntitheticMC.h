#include "Random1.h"
#include "Normals.h"
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

#pragma once
void AntitheticMC(double Expiry,
	double Strike,
	double Spot,
	double Vol,
	double r,
	double d,
	double OutBarrier,
	unsigned long NumberOfPaths,
	double TimeStep);