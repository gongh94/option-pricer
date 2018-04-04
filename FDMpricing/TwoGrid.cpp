#include <iostream>
#include <Eigen/Dense>
#include "smooth.h"
#include "JacobiSOR.h"

using namespace Eigen;
using namespace std;

int main()
{
	const int M = 10, N = 10;

	double B = 120, 
		K = 90,
		T = 1,
		r = 0.05,
		sigma = 0.3;

	double dx = B / N;

	double dt = T / M; // static uniform mesh size on t

	Matrix<double, N - 1, N - 1> Ql, Qr;
	Ql.fill(0);
	Qr.fill(0);

	Matrix<double, N - 1, M+1> v, defect, e; //Ql^{k+1}*u^{k+1} = Qr^{k+1}*u^k + R^k;
	v.fill(0);
	e.fill(0);
	defect.fill(0);

	//initialize v(0,x)
	for (int i = 0; i < N - 1; i++) {
		double temp = K - (i + 1)*dx;
		v(i,0) = (temp> 0) ? temp : 0;
	}

	double alpha, beta, gamma;

	for (int k = 0; k < M; k++) { // 1 -> M

		gamma = r * dt / 2;

		for (int i = 0; i < N - 1; i++) // i = 0,...,N-2
		{
			// j = i+1 = 1,...,N-1
			alpha = sigma * sigma / 4 * (i + 1) * dt;
			beta = r * (i + 1) / 4 * dt;

			Ql(i, i) = 1 + 2 * alpha + gamma;
			if (i != 0) Ql(i, i - 1) = -alpha + beta;
			if (i != N - 2) Ql(i, i + 1) = -alpha - beta;

			Qr(i, i) = 1 - 2 * alpha - gamma;
			if (i != 0) Qr(i, i - 1) = alpha - beta;
			if (i != N - 2) Qr(i, i + 1) = alpha + beta;

		}// end creating Ql, Qr

		MatrixXd Qtemp = Qr * v.col(k);
		Qtemp(0) -= (alpha - beta)*(K*exp(-r * k * dt) - K * exp(-r * (k+1)*dt)); // boundary correction term
		JacobiSOR(Ql, Qtemp, v.col(k+1), N - 1); // solve for v(k+1,x)
	}

	cout << "Before two-grid optimazation\n";
		cout << v << endl;

	/* ----------pre-smoothing---------- */
	smooth(v, N - 1, M + 1);

	//calculate defect
	for (int k = 0; k < M; k++) { // 1 -> M

		gamma = r * dt / 2;

		for (int i = 0; i < N - 1; i++) // i = 0,...,N-2
		{
			// j = i+1 = 1,...,N-1
			alpha = sigma * sigma / 4 * (i + 1) * dt;
			beta = r * (i + 1) / 4 * dt;

			Ql(i, i) = 1 + 2 * alpha + gamma;
			if (i != 0) Ql(i, i - 1) = -alpha + beta;
			if (i != N - 2) Ql(i, i + 1) = -alpha - beta;

			Qr(i, i) = 1 - 2 * alpha - gamma;
			if (i != 0) Qr(i, i - 1) = alpha - beta;
			if (i != N - 2) Qr(i, i + 1) = alpha + beta;

		}// end creating Ql, Qr

		MatrixXd Qtemp = Qr * v.col(k);
		Qtemp(0) -= (alpha - beta)*(K*exp(-r * k *dt) - K * exp(-r * (k+1)*dt)); // boundary correction term
		defect.col(k + 1) = Ql * v.col(k + 1) - Qtemp;
	
	}

	/* ----------fine to coarse---------- */

	const int M2 = M / 2;

	double dt2 = T / M2;

	Matrix<double, N - 1, M2+1> defect2;

	for (int i = 0; i < M2+1;i++)
	{
		defect2.col(i) = defect.col(2*i);
	}

	//cout << defect2 << endl;
	
	Matrix<double, M2 + 1, 1> t_H; // a col vector of time steps

	for (int i = 0; i < M2 + 1; i++) {
		t_H(i) = i * dt2;
	}

	Matrix<double, N - 1, M2 + 1> e_H; //Ql^{k+1}*u^{k+1} = Qr^{k+1}*u^k + R^k;
	e_H.fill(0);

	double alpha2, beta2, gamma2;

	for (int k = 0; k < M2; k++) 
	{ // 1 -> M

		gamma2 = r * dt2 / 2;

		for (int i = 0; i < N - 1; i++) // i = 0,...,N-2
		{
			// j = i+1 = 1,...,N-1
			alpha2 = sigma * sigma / 4 * (i + 1) * dt2;
			beta2 = r * (i + 1) / 4 * dt2;

			Ql(i, i) = 1 + 2 * alpha2 + gamma2;
			if (i != 0) Ql(i, i - 1) = -alpha2 + beta2;
			if (i != N - 2) Ql(i, i + 1) = -alpha2 - beta2;

			Qr(i, i) = 1 - 2 * alpha2 - gamma2;
			if (i != 0) Qr(i, i - 1) = alpha2 - beta2;
			if (i != N - 2) Qr(i, i + 1) = alpha2 + beta2;

		}// end creating Ql, Qr

		MatrixXd Qtemp = Qr * defect.col(k);
		Qtemp(0) -= (alpha2 - beta2)*(K*exp(-r * k *dt2) - K * exp(-r * (k+1) *dt2)); // boundary correction term
		JacobiSOR(Ql, Qtemp, e_H.col(k + 1), N - 1); // solve for v(k+1,x)
	}

	//cout << e_H << endl;

	/* ----------coarse to fine---------- */

	for (int i = 1; i < M2 + 1; i++)
	{
		e.col(2 * i) = e_H.col(i);
		e.col(2 * i - 1) = (e_H.col(i - 1) + e_H.col(i)) / 2;
	}
	
	//cout << e << endl;

	v = v + e;

	/* post-smoothing*/

	smooth(v, N - 1, M + 1);

	cout << "After two-grid optimization\n";
	cout << v << endl;
}

