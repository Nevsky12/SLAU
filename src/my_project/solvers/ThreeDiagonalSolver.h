//
// Created by alexander on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALSOLVER_H
#define MY_PROJECT_THREEDIAGONALSOLVER_H

#include <string>
#include <sstream>
#include "my_project/SlaeBaseException.hpp"
#include "my_project/matrix/ThreeDiagonalMatrix.h"

namespace Slae::Solvers{
    std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix& matrix, const std::vector<double>& col);
}


#endif //MY_PROJECT_THREEDIAGONALSOLVER_H
