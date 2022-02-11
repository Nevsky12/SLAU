//
// Created by alexander on 05.02.2022.
//

#ifndef MY_PROJECT_MATRIX_H
#define MY_PROJECT_MATRIX_H

#include "my_project/SlaeBaseException.hpp"
#include <vector>
#include <sstream>
#include <array>

namespace Slae::Matrix {

    class ThreeDiagonalMatrix {
        std::vector<std::array<double, 3>> data_;

    public:
        /* @brief Возвращает нулевую трёхдиагональную матрицу
         * Возвращает трёхдиагональую матрицу, полностью составленную из нулей
         *
         * @param size размер матрицы
         * @return нулевая трёхдиагональная матрица
        */
        static ThreeDiagonalMatrix Zero(int size);
        /* @brief Конструктор трёхдиагональной матрицы
         * Коструктор трёхдиагональной матрицы заданного размера
         *
         * @param size размер трёхдиагональной матрицы
        */
        explicit ThreeDiagonalMatrix(int size);
        /* @brief Возвращает число строк матрицы
         * Возвращает количество строк текущей трёхдиагональной матрицы
         *
         * @return число строк
        */
        [[nodiscard]] int rows() const noexcept;
        /* @brief Оператор разыменования элемента матрицы
         * Оператор получения доступа к элементу матрицы с данными индексами по ссылке
         *
         * @param i индекс строки элемента
         * @param j индекс столбца элемента
         * @return элемент с индексами i, j
         *
         * @throw SlaeBaseExceptionCpp выбрасывается, если данные индексы выходят за границы диапазона трёхдиагональной матрицы: i in {0, ..., data.size()}; j in {0, 1, 2}
        */
        double &operator()(int i, int j);
        /* @brief Оператор получения элемента матрицы
         * Оператор получения элемента с данными индексами по константной ссылке
         *
         * @param i индекс строки элемента
         * @param j индекс столбца элемента
         * @return элемент с индексами i, j
         *
         * @throw SlaeBaseExceptionCpp выбрасывается, если данные индексы выходят за границы диапазона трёхдиагональной матрицы: i in {0, ..., data.size()}; j in {0, 1, 2}
        */
        [[nodiscard]] const double &operator()(int i, int j) const;
    };

} // namespace Slae::Matrix



#endif //MY_PROJECT_MATRIX_H
