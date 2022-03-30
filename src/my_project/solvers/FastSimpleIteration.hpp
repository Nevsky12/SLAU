//
// Created by alexander on 19.03.2022.
//

#ifndef MY_PROJECT_FASTSIMPLEITERATION_HPP
#define MY_PROJECT_FASTSIMPLEITERATION_HPP
#include "my_project/SlaeBaseException.hpp"
#include "my_project/sparse/CSR.hpp"
#include <vector>
#include <iosfwd>
#include <sstream>
#include "my_project/Chebyshev/Chebyshev.hpp"
#include "my_project/utility/Overloads.hpp"
#include "my_project/utility/Norm.hpp"
namespace Slae::Solvers {
    template<typename T, int powOf2>
    std::vector<T>
    FastSimpleIteration(const Matrix::CSR <T> &A, const Matrix::CSR <T> &A_reverse, const std::vector<T> &b,
                        const std::vector<T> &initialState, std::pair<T, T> &borders)
    {
#ifndef NDEBUG
        if (A.rows_number() != b.size())
        {
            std::stringstream buff;
            buff << "Matrix and column dimensions are not equal! Matrix size: " << A.rows_number() << "x" << A.cols_number()
                 << ". Column size: "<< b.size() << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        if (A.rows_number() != A.cols_number())
        {
            std::stringstream buff;
            buff << "Matrix dimensions are not equal! Matrix size: " << A.rows_number() << "x" << A.cols_number()
                 << ". File: " << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }

        if (initialState.size() != b.size())
        {
            std::stringstream buff;
            buff << "Vector of constant terms and initial state vector dimensions are not equal! Vector b size: "
                 << b.size() << ". Initial state column size: "<< initialState.size() << ". File: "
                 << __FILE__ << ". Line: " << __LINE__;

            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif //NDEBUG

        std::vector<T> tao_roots = ChebyshevPolinomial<T, powOf2>::CalculateRoots(borders);
        std::vector<T> currentState = initialState;
        std::vector<T> r = A * currentState - b;
        std::cout << currentState << std::endl;
//        std::vector<T> eps;
        std::vector<T> count;
        int counter = 0;
//        eps.push_back(norm(A_reverse * r, NormType::ThirdNorm));
        count.push_back(counter);
        for (int i = 0; i < powOf2; i++)
        {
            ++counter;
            count.push_back(counter);
            currentState = currentState - (r * (1 / tao_roots[i]));
            r = A * currentState - b;
            std::cout << currentState << std::endl;
//            eps.push_back(norm(A_reverse * r, NormType::ThirdNorm));
        }
//        std::cout << count;
//        std::cout << std::endl;
//        std::cout << eps;
        return currentState;
    }
} // namespace Slae::Solvers
#endif //MY_PROJECT_FASTSIMPLEITERATION_HPP
