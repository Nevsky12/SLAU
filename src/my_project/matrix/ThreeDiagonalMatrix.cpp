//
// Created by alexander on 05.02.2022.
//

#include "ThreeDiagonalMatrix.hpp"
#include <iostream>

namespace Slae::Matrix {

    ThreeDiagonalMatrix::ThreeDiagonalMatrix(int size) : data_(size) {}

    double &ThreeDiagonalMatrix::operator()(int i, int j) {
#ifndef NDEBUG
        if (i >= static_cast<int>(data_.size())) {
            std::stringstream buf;
            buf << "Index i out of range! Input index"  << i << ". Matrix size: " << data_.size() << "Файл: " << __FILE__ << ". Строка: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        }
        if (j > 2) {
        std::stringstream buf;
        buf << "Index i must be in {0, 1, 2}! Input index"  << j << "Файл: " << __FILE__ << ". Строка: " << __LINE__;
        throw SlaeBaseExceptionCpp(buf.str());
    }
#endif //NDEBUG
    return data_[i][j];
    }


    const double &ThreeDiagonalMatrix::operator()(int i, int j) const {
#ifndef NDEBUG
        if (i >= static_cast<int>(data_.size())) {
            std::stringstream buf;
            buf << "Index i out of range! Input index"  << i << ". Matrix size: " << data_.size() << "Файл: " << __FILE__ << ". Строка: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        }
        if (j > 2) {
        std::stringstream buf;
        buf << "Index i must be in {0, 1, 2}! Input index"  << j << "Файл: " << __FILE__ << ". Строка: " << __LINE__;
        throw SlaeBaseExceptionCpp(buf.str());
    }
#endif //NDEBUG
        return data_[i][j];
    }

    ThreeDiagonalMatrix ThreeDiagonalMatrix::Zero(int size) {
        ThreeDiagonalMatrix res(size);
        for (auto& string: res.data_) {
            string = {0., 0., 0.};
        }
        return res;
    }

}

int Slae::Matrix::ThreeDiagonalMatrix::rows() const noexcept {
    return static_cast<int>(data_.size());
}