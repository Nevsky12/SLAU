//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_SIMPLEITERATION_HPP
#define SLAE_SIMPLEITERATION_HPP

#include "../sparse/CSR.hpp"
#include "../utility/Norm.hpp"
#include "../utility/Overloads.hpp"

namespace Slae::Solvers {
    /* @brief Метод решает СЛАУ при помощи метода простых итераций
* Данный метод решает систему линейный алгебраических уравнений с правой частью при помощи метода простых итераций. О
* методе простых итераций можно узнать из книги Березина "Методы вычислений. Том второй"
*
* @param A матрица CSR
* @param b вектор-столбец правой части СЛАУ
* @param tao величина тау для данного метода
* @return решение СЛАУ
*
*
* @throw SlaeBaseExceptionCpp выбрасывается, если строк матрицы и высота столбца не совпадают
*/
    template<typename T>
    std::vector<T> SimpleIteration(const Slae::Matrix::CSR<T> &A, const std::vector<T> &b, const T &tao) {
        if (A.rows_number() != b.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << A.rows_number() << ". Col size: " << A.cols_number()
                << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        } else {
            std::vector<T> initialState;
            initialState.resize(A.rows_number(), static_cast<T>(0));
            std::vector<T> r = A * initialState - b;
            std::vector<T> currentState = initialState;
            std::vector<T> tempState(currentState.size());
            while (norm(r, NormType::ThirdNorm) > tao) {
                tempState = currentState - tao * (A * currentState - b);
                currentState = tempState;
                r = A * currentState - b;
            }
            return currentState;
        }
    }
} //Slae::Solvers

#endif//SLAE_SIMPLEITERATION_HPP
