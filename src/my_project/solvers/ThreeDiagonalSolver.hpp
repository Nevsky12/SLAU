//
// Created by alexander on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALSOLVER_H
#define MY_PROJECT_THREEDIAGONALSOLVER_H

#include <string>
#include <sstream>
#include "my_project/SlaeBaseException.hpp"
#include "my_project/matrix/ThreeDiagonalMatrix.hpp"

namespace Slae::Solvers{
     /* @brief Метод решает СЛАУ при помощи метода прогонки
     * Данный метод решает систему линейный алгебраических уравнений с правой частью при помощи метода прогонки. О
     * методе прогонки можно узнать из книги Демченко "Упражнения и задачи контрольных работы по вычислительной математике. Часть 1"
     *
     * @param matrix трёхдиагональная матрица
     * @param col вектор-столбец правой части СЛАУ
     * @return решение СЛАУ
     *
     *
     * @throw SlaeBaseExceptionCpp выбрасывается, если строк матрицы и высота столбца не совпадают
    */
    [[nodiscard]] std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix& matrix, const std::vector<double>& col);
}


#endif //MY_PROJECT_THREEDIAGONALSOLVER_H
