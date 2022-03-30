//
// Created by alexander on 19.03.2022.
//

#ifndef MY_PROJECT_STEEPESTGRADIENTDESCENT_HPP
#define MY_PROJECT_STEEPESTGRADIENTDESCENT_HPP
#include <vector>
#include "my_project/sparse/CSR.hpp"
#include "my_project/utility/Norm.hpp"
#include "my_project/utility/Overloads.hpp"
namespace Slae::Solvers {
    template<typename T>
    std::vector<T> SteepestGradientDescent(const Slae::Matrix::CSR<T> &A, const Slae::Matrix::CSR<T> &A_reverse, const std::vector<T> &b, T tao, int N, const std::vector<T>& initialState) {
        if (A.rows_number() != b.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << A.rows_number() << ". Col size: " << A.cols_number()
                << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw Slae::SlaeBaseExceptionCpp(buf.str());
        } else {
            int counter = 0;
            std::vector<T> r = A * initialState - b;
//            std::vector<T> eps;
            std::vector<T> count;
            count.push_back(counter);
            std::vector<T> currentState = initialState;
            std::vector<T> tempState(currentState.size());
            std::cout << currentState << std::endl;
            T alpha = (r * r) / (r * (A * r));
//            eps.push_back(norm(A_reverse * r, NormType::ThirdNorm));
            while (norm(r, NormType::ThirdNorm) > tao) {
                if (counter < N) {
                    tempState = currentState - alpha * r;
                    currentState = tempState;
                    r = A * currentState - b;
//                eps.push_back(norm(A_reverse * r, NormType::ThirdNorm));
                    alpha = (r * r) / (r * (A * r));
                    ++counter;
                    count.push_back(counter);
                    std::cout << currentState << std::endl;
                } else {
                    break;
                }
            }
//            std::cout << count;
//            std::cout << std::endl;
//            std::cout << eps;
            return currentState;
        }
    }
} //namespace SteepestGradientDescent
#endif //MY_PROJECT_STEEPESTGRADIENTDESCENT_HPP
