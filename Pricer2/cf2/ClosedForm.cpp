#include "ClosedForm.h"

void ClosedForm(double Expiry,
	double Strike,
	double Spot,
	double Vol,
	double r,
	double d, // how does dividend come into play?
	double OutBarrier,
	unsigned long NumberOfPaths)
{
	clock_t tStart = clock();

	double delta_plus_SK = (log(Spot / Strike) + (r + Vol * Vol / 2)*Expiry) / (Vol*sqrt(Expiry));
	double delta_plus_SB = (log(Spot / OutBarrier) + (r + Vol * Vol / 2)*Expiry) / (Vol*sqrt(Expiry));
	
	double delta_minus_SK = (log(Spot / Strike) + (r - Vol * Vol / 2)*Expiry) / (Vol*sqrt(Expiry));
	double delta_minus_SB = (log(Spot / OutBarrier) + (r - Vol * Vol / 2)*Expiry) / (Vol*sqrt(Expiry));

	double delta_plus_Bsq= (log(OutBarrier*OutBarrier / (Strike*Spot)) + (r + Vol * Vol / 2)*Expiry) / (Vol*sqrt(Expiry));
	double delta_plus_BS = (log(OutBarrier / Spot) + (r + Vol * Vol / 2)*Expiry) / (Vol*sqrt(Expiry));
	
	double delta_minus_Bsq= (log(OutBarrier*OutBarrier / (Strike*Spot)) + (r - Vol * Vol / 2)*Expiry) / (Vol*sqrt(Expiry));
	double delta_minus_BS= (log(OutBarrier / Spot) + (r - Vol * Vol / 2)*Expiry) / (Vol*sqrt(Expiry));
	

	

	double T1 = Spot * (CumulativeNormal(delta_plus_SK) - CumulativeNormal(delta_plus_SB));
	double T2 = -exp(-r * Expiry) * Strike * (CumulativeNormal(delta_minus_SK) - CumulativeNormal(delta_minus_SB));
	double T3 = - OutBarrier* pow((Spot / OutBarrier), -2 * r / (Vol*Vol)) * (CumulativeNormal(delta_plus_Bsq) - CumulativeNormal(delta_plus_BS));
	double T4 = exp(-r * Expiry) * Strike * pow(Spot / OutBarrier, -2 * r / (Vol*Vol) + 1) * (CumulativeNormal(delta_minus_Bsq) - CumulativeNormal(delta_minus_BS));

	double result = (T1 + T2 + T3 + T4);

	cout << "Closed-form barrier option price = " << result << "," << " ";
	cout << "run time = " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "s\n\n";

} 