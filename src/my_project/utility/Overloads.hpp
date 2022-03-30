//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_OVERLOADS_HPP
#define SLAE_OVERLOADS_HPP
#include <iosfwd>
#include <vector>
/***
 * Умножение числа на вектор
 * @tparam T Тип числа
 * @param k Число
 * @param b Вектор
 * @return Результат умножения
 */
template<typename T>
std::vector<T> operator*(const T &k, const std::vector<T> &b) {
    std::vector<T> temp(b.size(), static_cast<T>(0));
    for (std::size_t i = 0; i < b.size(); ++i) {
        temp[i] = b[i] * k;
    }
    return temp;
}

/***
 * Умножение вектора на число
 * @tparam T Тип числа
 * @param b Вектор
 * @param k Число
 * @return Результат умножения
 */
template<typename T>
std::vector<T> operator*(const std::vector<T> &b, const T &k) {
    std::vector<T> temp(b.size(), static_cast<T>(0));
    for (std::size_t i = 0; i < b.size(); ++i) {
        temp[i] = b[i] * k;
    }
    return temp;
}

/***
 * Скалярное перемножение векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат скалярного перемножения
 */
template<typename T>
T operator*(const std::vector<T> &a, const std::vector<T> &b) {
    T res;
    for (int i = 0; i < a.size(); ++i) {
        res += a[i] * b[i];
    }
    return res;
}

/***
 * Вычитание двух векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат вычитания векторов
 */
template<typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> temp;
    temp.resize(a.size(), static_cast<T>(0));
    for (int i = 0; i < a.size(); ++i) {
        temp[i] = a[i] - b[i];
    }
    return temp;
}

/***
 * Сложение двух векторов
 * @tparam T Тип элементов векторов
 * @param a Первый вектор
 * @param b Второй вектор
 * @return Результат сложения векторов
 */
template<typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> temp;
    temp.resize(a.size(), static_cast<T>(0));
    for (int i = 0; i < a.size(); ++i) {
        temp[i] = a[i] + b[i];
    }
    return temp;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &b) {
    for (int i = 0; i < b.size(); ++i) {
        os << b[i] << " ";
    }
    return os;
}

#endif//SLAE_OVERLOADS_HPP
