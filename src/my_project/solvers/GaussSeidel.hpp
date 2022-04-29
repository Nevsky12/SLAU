//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_GAUSSSEIDEL_HPP
#define SLAE_GAUSSSEIDEL_HPP

#include "../sparse/CSR.hpp"
#include "../utility/Norm.hpp"
#include "../utility/Overloads.hpp"

namespace Slae::Solvers {
    template<typename T>
    std::vector<T>
    GaussSeidelIter(const Slae::Matrix::CSR<T> &A, const std::vector<T> &b, std::vector<T> x) {
        T sum;
        for (int i = 0; i < A.rows_number(); ++i) {
            int skip = A.rows_[i];
            int count = A.rows_[i + 1] - skip;
            for (int k = skip; k < skip + count; ++k) {
                if (A.cols_[k] != i) sum += A.values_[k] * x[i];
            }
            x[i] = (b[i] - sum) / A(i, i);
        }
        return x;
    }

/* @brief Метод решает СЛАУ при помощи метода Гаусса-Зейделя
* Данный метод решает систему линейный алгебраических уравнений с правой частью при помощи метода Гаусса-Зейделя. О
* методе Гаусса-Зейделя можно узнать из книги Березина "Методы вычислений. Том второй"
*
* @param A матрица CSR
* @param b вектор-столбец правой части СЛАУ
* @param initialState начальное приближение
 *  @param tolerance точность, с которой хотим получить решение
* @return решение СЛАУ
*
*
* @throw SlaeBaseExceptionCpp выбрасывается, если строк матрицы и высота столбца не совпадают
*/
    template<typename T>
    std::vector<T>
    GaussSeidel(const Slae::Matrix::CSR<T> &A, const std::vector<T> &b, const std::vector<T> &initialState,
                const T &tolerance) {
        if (A.rows_number() != b.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << A.rows_number() << ". Col size: " << A.cols_number()
                << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        } else {
            std::vector<T> r = A * initialState - b;
            std::vector<T> currentState = initialState;
            while (norm(r, NormType::ThirdNorm) > tolerance) {
                currentState = GaussSeidelIter<T>(A, b, currentState);
                r = A * currentState - b;
            }
            return currentState;
        }
    }

    template<typename T>
    std::vector<T>
    FastGaussSeidel(const Slae::Matrix::CSR<T> &A, const std::vector<T> &b, const std::vector<T> &initialState, T rho,
                    const T &tolerance) {
        if (A.rows_number() != b.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << A.rows_number() << ". Col size: " << A.cols_number()
                << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        } else {
            std::vector<T> currentState = GaussSeidelIter<T>(A, b,initialState);
            std::vector<T> prevState = initialState;
            std::vector<T> nextState = currentState;
            std::vector<T> r = A * nextState - b;
            auto mu0 = static_cast<T>(1.);
            auto mu1 = static_cast<T>(1.) / rho;
            auto mu2 = static_cast<T>(2.) / rho * mu1 - mu0;
            while (norm(r, NormType::ThirdNorm) > tolerance) {
                nextState = static_cast<T>(2.) * mu1 / rho / mu2 * GaussSeidelIter(A, b, currentState) - mu0 / mu2 * prevState;
                r = A * nextState - b;
                prevState = currentState;
                currentState = nextState;
                mu0 = mu1;
                mu1 = mu2;
                mu2 = static_cast<T>(2.) / rho * mu1 - mu0;
            }
            return currentState;
        }
    }
} //Slae::Solvers

#endif//SLAE_GAUSSSEIDEL_HPP
