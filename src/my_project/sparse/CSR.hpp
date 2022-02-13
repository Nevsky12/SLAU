//
// Created by petrov on 12.02.2022.
//

#ifndef SOLE2022_CSR_HPP
#define SOLE2022_CSR_HPP

#include <vector>
#include <set>
#include <iosfwd>

#include "../utility/Triplet.hpp"
#include "../SlaeBaseException.hpp"

namespace Slae::Matrix {

    template<typename T>
    class CSR {
    public:
        using elm_t = T;          // Тип данных элементов матрицы
        using idx_t = std::size_t;// Тип индекса

    private:
        const idx_t H_, W_;          //Размеры матрицы
        std::vector<elm_t> values_;  //Вектор значений (размер N - кол-во ненулевых элементов)
        std::vector<idx_t> cols_;    // Вектор номеров столбцов, соответствующих значениям (размер N - кол-во ненулевых элементов)
        std::vector<idx_t> rows_;    // Вектор индексации строк размера H+1, первый элемент = 0 в качестве запирающего

    public:
        /* @brief Конструктор разреженной матрицы по данным векторам
         * Конструктор матрицы CSR на основе получаемых векторов, содержащих всю информацию о значениях; номерах стобцов, соответствующим значениям ненулевых
         * элементов; индексации строк, где первый жэлемент - запирающиц нуль
         *
         * @param h число строк
         * @param w число столбцов
         * @param v вектор ненулевых значений
         * @param c вектор индексации столбцов
         * @param r вектор индексации строк
        */
        CSR(const idx_t &h, const idx_t &w, const std::vector<T> &v, const std::vector<T> &c, const std::vector<T> &r)
                : H_(h), W_(w), values_(v), cols_(c), rows_(r) {}

        /* @brief Конструктор разреженной матрицы по сету из Triplet
        * Конструктор матрицы CSR на основе получаемого std::set из структур Triplet, информацию о которой можно узнать из файла Triplet.hpp данного проекта
        *
        * @param h число строк
        * @param w число столбцов
        * @param in множество из структур Triplet с данными для каждого ненулевого элемента
       */
        CSR(const idx_t &h, const idx_t &w, const std::set<Slae::Triplet::Triplet<elm_t>> &in) : H_(h), W_(w) {
            values_.resize(in.size());
            cols_.resize(in.size());
            rows_.resize(h + 1);
            int countInRow = 0;     //количество ненулевых элементов в данной строке
            int currRow = 0;        //текущая строка,элементы которой мы заполняем
            auto it = in.begin();
            for (idx_t k = 0; k < in.size(); ++k) {
                while (currRow < it->i) {
                    rows_[currRow + 1] = rows_[currRow] + countInRow;
                    ++currRow;
                    countInRow = 0;
                }
                values_[k] = it->value;
                cols_[k] = it->j;
                ++countInRow;
                it = std::next(it);
            }
            for (++currRow; currRow <= H_; ++currRow) {
                rows_[currRow] = in.size();
            }
        }

        /* @brief Оператор получения элемента матрицы
         * Оператор получения элемента с данными индексами по константной ссылке
         *
         * @param i индекс строки элемента
         * @param j индекс столбца элемента
         * @return элемент с индексами i, j
         *
         * @throw SlaeBaseExceptionCpp выбрасывается, если данные индексы выходят за границы диапазона трёхдиагональной матрицы: i in {0, ..., rows_.data()}; j in {0, ..., cols_data()}
        */
        [[nodiscard]] const elm_t &operator()(idx_t const i, idx_t const j) const {
#ifndef NDEBUG
            if (i > rows_.size() || i < 0) {
                std::stringstream buf;
                buf << "Index i out of range! Input index" << i << ". Matrix size: " << rows_.size() << "Файл: "
                    << __FILE__ << ". Строка: " << __LINE__;
                throw Slae::SlaeBaseExceptionCpp(buf.str());
            }
            if (j > cols_.size() || j < 0) {
                std::stringstream buf;
                buf << "Index j out of range! Input index" << j << ". Matrix size: " << cols_.size() << "Файл: "
                    << __FILE__ << ". Строка: " << __LINE__;
                throw Slae::SlaeBaseExceptionCpp(buf.str());
            }
#endif
            idx_t skip = this->rows_[i];
            for (idx_t k = skip; k < this->rows_[i + 1]; ++k) {
                if (this->cols_[k] == j) return this->values_[k];
            }
            return static_cast<elm_t>(0);
        }

        /* @brief Оператор получения элемента матрицы
       * Оператор получения элемента с данными индексами по ссылке
       *
       * @param i индекс строки элемента
       * @param j индекс столбца элемента
       * @return элемент с индексами i, j
       *
       * @throw SlaeBaseExceptionCpp выбрасывается, если данные индексы выходят за границы диапазона трёхдиагональной матрицы: i in {0, ..., rows_.data()}; j in {0, ..., cols_data()}
      */
        elm_t &operator()(idx_t const i, idx_t const j) {
#ifndef NDEBUG
            if (i > rows_.size() || i < 0) {
                std::stringstream buf;
                buf << "Index i out of range! Input index" << i << ". Matrix size: " << rows_.size() << "Файл: "
                    << __FILE__ << ". Строка: " << __LINE__;
                throw Slae::SlaeBaseExceptionCpp(buf.str());
            }
            if (j > cols_.size() || j < 0) {
                std::stringstream buf;
                buf << "Index j out of range! Input index" << j << ". Matrix size: " << cols_.size() << "Файл: "
                    << __FILE__ << ". Строка: " << __LINE__;
                throw Slae::SlaeBaseExceptionCpp(buf.str());
            }
#endif
            idx_t skip = this->rows_[i];
            for (idx_t k = skip; k < this->rows_[i + 1]; ++k) {
                if (this->cols_[k] == j) return this->values_[k];
            }
            return static_cast<elm_t>(0);
        }

        /* @brief Оператор умножения матрицы на вектор
          * Оператор умножения матрицы CSR на вектор-столбец по правилам умножения матрицы CSR на вектор
          *
          * @param b вектор, на который умножается матрица CSR
          * @return вектор, являющийся результатом перемножения матрицы на вектор b
          *
          * @throw SlaeBaseExceptionCpp выбрасывается, если размер вектора b не равен числу строк матрицы
         */
        std::vector<elm_t> operator*(const std::vector<elm_t> &b) const {
            std::vector<elm_t> res(this->H_);
            for (idx_t i = 0; i < H_; ++i) {
                idx_t skip = this->rows_[i];
                idx_t count = this->rows_[i + 1] - skip;
                for (idx_t k = skip; k < skip + count; ++k) {
                    res[i] += values_[k] * b[cols_[k]];
                }
            }
            return res;
        }

        /* @brief Возвращает число строк матрицы
         * Возвращает количество строк текущей разреженной матрицы
         *
         * @return число строк
        */
        [[nodiscard]] idx_t rows() const noexcept {
            return rows_.size() - 1;
        }

        /* @brief Возвращает число фактических столбцов матрицы
         * Возвращает количество фактических столбцов текущей разреженной матрицы
         *
         * @return число фактических столбцов
        */
        [[nodiscard]] idx_t cols() const noexcept{
            std::set<T> s(std::make_move_iterator(cols_.begin()),
                          std::make_move_iterator(cols_.end()));
            return s.size();
        }
    };
} //Slae::CSR

#endif //SOLE2022_CSR_HPP
