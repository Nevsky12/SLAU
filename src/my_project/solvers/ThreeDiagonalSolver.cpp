//
// Created by alexander on 05.02.2022.
//

#include "ThreeDiagonalSolver.hpp"

namespace Slae::Solvers{
    std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix& matrix, const std::vector<double>& col) {
        if (matrix.rows() != col.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << matrix.rows() << ". Col size: " << col.size() << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        } else {
            int size = static_cast<int>(matrix.rows());
            std::vector<std::array<double, 2>> RunThroughCoefficients(size);
            RunThroughCoefficients[0][0] = -matrix(0, 2) / matrix(0, 1);
            RunThroughCoefficients[0][1] = col[0] / matrix(0, 1);
            for (int i = 1; i < size; ++i) {
                RunThroughCoefficients[i][0] = -matrix(i, 2) / (RunThroughCoefficients[i - 1][0] * matrix(i, 0) + matrix(i, 1));
                RunThroughCoefficients[i][1] = (col[i] - matrix(i, 0) * RunThroughCoefficients[i - 1][1]) / (RunThroughCoefficients[i - 1][0] * matrix(i, 0) + matrix(i, 1));
            }
            std::vector<double> res(size);
            res[size - 1] = (col.back() - matrix(size - 1, 0) * RunThroughCoefficients[size - 1][1]) / (matrix(size - 1, 0) * RunThroughCoefficients[size - 2][0]);
            for (int i = size - 2;i >= 0; --i) {
                res[i] = RunThroughCoefficients[i][0] * res[i + 1] + RunThroughCoefficients[i][1];
            }
            return res;
        }
    }
} //Slae::Solvers