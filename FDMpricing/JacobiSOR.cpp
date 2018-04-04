#include "JacobiSOR.h"

void JacobiSOR(const Ref<MatrixXd>& M, const Ref<MatrixXd>& q, Ref<MatrixXd> u, int size)
{
	//Mv=q;
	MatrixXd D(size, size), U(size, size), L(size, size), Dinv(size, size);

	Dinv.fill(0);
	D.fill(0);
	U.fill(0);
	L.fill(0);

	D.diagonal() = M.diagonal();
	U.diagonal(1) = M.diagonal(1);
	L.diagonal(-1) = M.diagonal(-1);

	for (int i = 0; i < size; i++)
	{
		Dinv(i, i) = 1 / D(i, i);
	}

	for (int k = 0; k < 10; k++)
	{
		u = Dinv * (q - (U + L)*u);
	}

	//cout << Dinv << endl;
	//cout << D << endl;
	//cout << U << endl;
	//cout << L << endl;
}