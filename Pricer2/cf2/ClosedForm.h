#pragma once
#include "Random1.h"
#include "Normals.h"
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;

void ClosedForm(double Expiry,
	double Strike,
	double Spot,
	double Vol,
	double r,
	double d,
	double OutBarrier,
	unsigned long NumberOfPaths);