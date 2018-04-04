#pragma once
#include <Eigen/Dense>

using namespace Eigen;

void JacobiSOR(const Ref<MatrixXd>& M, const Ref<MatrixXd>& q, Ref<MatrixXd> u, int size);