#pragma once
#include <Eigen/Dense>
using namespace Eigen;

void smooth(Ref<MatrixXd> U, int rsize, int csize);