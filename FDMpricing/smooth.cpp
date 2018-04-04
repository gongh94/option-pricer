#include "smooth.h"

// smoothing in red-black ordering

void smooth(Ref<MatrixXd> M, int rsize, int csize)
{
	double T = 1, sigma = 0.3, r = 0.05;
	double dt = T / csize;
	// suppose rsize, csize are odd
	double a, b, c;
	bool isRed = false;

	for (int k = 1; k < csize; k++) {
		for (int j = 1; j < rsize - 1; j++)
		{
			if ((k + j) % 2 == 0)
			{
				a = 1 / 2 * sigma*sigma*j*j*dt;
				b = r * j / 2 * dt;
				c = r * dt;
				M(j, k) = (a + b)*M(j + 1, k) + (1 - 2 * a - c)*M(j, k) + (a - b)*M(j - 1, k);
			}
		}
	}

	for (int k = 1; k < csize; k++) {
		for (int j = 1; j < rsize - 1; j++)
		{
			if ((k + j) % 2 != 0)
			{
				a = 1 / 2 * sigma*sigma*j*j*dt;
				b = r * j / 2 * dt;
				c = r * dt;
				M(j, k) = (a + b)*M(j + 1, k) + (1 - 2 * a - c)*M(j, k) + (a - b)*M(j - 1, k);
			}
		}
	}


}