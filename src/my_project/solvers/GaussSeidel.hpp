//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_GAUSSSEIDEL_HPP
#define SLAE_GAUSSSEIDEL_HPP

#include "../sparse/CSR.hpp"
#include "../utility/Norm.hpp"
#include "../utility/Overloads.hpp"

namespace Slae::Solvers {
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
            std::vector<T> tempState(currentState.size());
            T sum;
            while (norm(r, NormType::ThirdNorm) > tolerance) {
                sum = static_cast<T>(0);
                for (int i = 0; i < A.rows_number(); ++i) {
                    int skip = A.rows_[i];
                    int count = A.rows_[i + 1] - skip;
                    for (int k = skip; k < skip + count; ++k) {
                        if (A.cols_[k] != i) sum += A.values_[k] * currentState[i];
                    }
                    currentState[i] = (b[i] - sum) / A(i, i);
                }
                r = A * currentState - b;
            }
            return currentState;
        }
    }
} //Slae::Solvers

#endif//SLAE_GAUSSSEIDEL_HPP
