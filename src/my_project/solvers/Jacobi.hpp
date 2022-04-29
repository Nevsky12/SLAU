//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_JACOBI_HPP
#define SLAE_JACOBI_HPP

#include "../sparse/CSR.hpp"
#include "../utility/Norm.hpp"
#include "../utility/Overloads.hpp"

namespace Slae::Solvers {
    /* @brief Метод решает СЛАУ при помощи метода Якоби
  * Данный метод решает систему линейный алгебраических уравнений с правой частью при помощи метода Якоби. О
  * методе Якоби можно узнать из книги Березина "Методы вычислений. Том второй"
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
    template<typename El>
    std::vector<El>
    Jacobi(const Slae::Matrix::CSR<El> &A, const std::vector<El> &b, const std::vector<El> &initialState,
           const El &tolerance) {
        if (A.rows_number() != b.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << A.rows_number() << ". Col size: " << A.cols_number()
                << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        } else {
            std::vector<El> r = A * initialState - b;
            std::vector<El> currentState = initialState;
            std::vector<El> tempState(currentState.size());
            El sum;
            while (norm(r, NormType::ThirdNorm) > tolerance) {
                sum = static_cast<El>(0);
                for (int i = 0; i < A.rows_number(); ++i) {
                    int skip = A.rows_[i];
                    int count = A.rows_[i + 1] - skip;
                    for (int k = skip; k < skip + count; ++k) {
                        if (A.cols_[k] != i) sum += A.values_[k] * currentState[i];
                    }
                    tempState[i] = (b[i] - sum) / A(i, i);
                }
                currentState = tempState;
                r = A * currentState - b;
            }
            return currentState;
        }
    }
} //Slae::Solvers

#endif//SLAE_JACOBI_HPP
