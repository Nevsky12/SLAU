//
// Created by alexander on 05.02.2022.
//

#include "ThreeDiagonalSolver.h"

namespace Slae::Solvers{
    std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix& matrix, const std::vector<double>& col) {
        if (matrix.rows() != col.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << matrix.rows() << ". Col size: " << col.size() << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        } else {
            int size = matrix.rows();
            std::vector<std::array<double, 2>> RunThroughCoefficients(size);
            RunThroughCoefficients[0][0] = -matrix(0, 2) / matrix(0, 1);
            RunThroughCoefficients[0][1] = -matrix(0, 3) / matrix(0, 1);
            for (int i = 1; i < size; ++i) {
                RunThroughCoefficients.at(i).at(0) = -matrix(i, 2) / (RunThroughCoefficients.at(i - 1).at(0) * matrix(i, 0) + matrix(i, 1));
                RunThroughCoefficients.at(i).at(1) = (matrix(i, 3) - matrix(i, 0) * matrix(i - 1, 1)) / (RunThroughCoefficients.at(i - 1).at(1) * matrix(i, 0) + matrix(i, 1));
            }
            std::vector<double> res(size);
            res.at(size - 1) = (matrix(size - 1, 3) - matrix(size - 1, 0) * RunThroughCoefficients.at(size - 1).at(1)) / (matrix(size - 1, 0) * RunThroughCoefficients.at(size - 2).at(0));
            for (int i = size - 2;i >= 0; --i) {
                res.at(i) = RunThroughCoefficients.at(i).at(0) * res.at(i + 1) + RunThroughCoefficients.at(i).at(1);
            }
            return res;
        }
    }
} //Slae::Solvers