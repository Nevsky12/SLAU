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

        std::vector<std::array<double, 4>> data_;


    public:

        static ThreeDiagonalMatrix Zero(int size);
        explicit ThreeDiagonalMatrix(int size);

        [[nodiscard]] int rows() const noexcept;
        double &operator()(int i, int j);

        [[nodiscard]] const double &operator()(int i, int j) const;
    };

} // namespace Slae::Matrix



#endif //MY_PROJECT_MATRIX_H
