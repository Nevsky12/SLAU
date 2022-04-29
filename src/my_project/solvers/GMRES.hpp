//
// Created by alexander on 22.04.22.
//

#ifndef MY_PROJECT_GMRES_HPP
#define MY_PROJECT_GMRES_HPP

#include "../sparse/CSR.hpp"
#include "../dense/Densematrix.hpp"
#include "../utility/Norm.hpp"
#include "../utility/Overloads.hpp"

namespace Slae::Solvers {

    template<typename T>
    std::tuple<std::vector<T>, std::vector<T>> arnoldiAlgorithm(const DenseMatrix<T> &A, const std::array<std::vector<T>, 4> &R, int iter) {
        int k = iter;
        auto krylovVector = A * R[k - 1];
        std::vector<T> h(k, static_cast<T>(0));
        for (int i = 0; i < k; ++i) {
            auto temp = R[i];
            h[i] = temp * krylovVector;
            krylovVector = krylovVector - h[i] * temp;
        }
        h[k] = norm(krylovVector, NormType::SecondNorm);
        krylovVector = krylovVector * (1 / h[k]);
        return std::make_tuple(h, krylovVector);
    }

    template<typename T>
    std::tuple<T, T> updateGivensRotations(T value1, T value2) {
        T t = std::sqrt(value1 * value1 + value2 * value2);
        T cs = value1 * (1 / t);
        T sn = value2 * (1 / t);
        return std::make_tuple(cs, sn);
    }

    template<typename T>
    std::tuple<std::vector<T>, T, T>
    applyGivensRotation(std::vector<T> &h, std::vector<T> &cs, std::vector<T> sn, int iter) {
        int k = iter;
        for (int i = 0; i < k - 1; ++i) {
            auto temp = cs[i] * h[i] + sn[i] * h[i + 1];
            h[i + 1] = -sn[i] * h[i] + cs[i] * h[i + 1];
            h[i] = temp;
        }
        T cs_currentIteration, sn_currentIteration;
        std::tie(cs_currentIteration, sn_currentIteration) = updateGivensRotations(h[k - 1], h[k]);
        h[k - 1] = cs_currentIteration * h[k - 1] + sn_currentIteration * h[k];
        h[k] = static_cast<T>(0);
        return std::make_tuple(h, cs_currentIteration, sn_currentIteration);
    }

    template<typename T>
    std::vector<T>
    GMRES(const DenseMatrix<T> &A, const std::vector<T> &b, const std::vector<T> &initialState, T tolerance, int maxIterations = 4) {

        int m = maxIterations;
        auto r = A * initialState - b;
        T r_norm = norm(r, NormType::SecondNorm);
        T b_norm = norm(b, NormType::SecondNorm);
        T err = norm(r, NormType::SecondNorm) / b_norm;
        std::vector<T> err_v;
        err_v.push_back(err);
        std::vector<T> sn(m, static_cast<T>(0));
        std::vector<T> cs(m, static_cast<T>(0));
        std::vector<T> e1(m + 1, static_cast<T>(0));
        e1[0] = static_cast<T>(1);
        std::array<std::vector<T>, 4> R;
        DenseMatrix<T> H(m + 1, m);
        R[0] = r * (-1 / r_norm);
        auto betaVector = r_norm * e1;

        for (int j = 0; j < m; ++j) {

            auto &&tempH = slice(H.slice_w(j), static_cast<T>(0), j + 1);
            auto &&tempR = R[j + 1];
            std::tie(tempH, tempR) = arnoldiAlgorithm(A, R, j);
            T cs_currentIteration = cs[j];
            T sn_currentIteration = sn[j];
            std::tie(tempH, cs_currentIteration, sn_currentIteration) = applyGivensRotation(tempH, cs, sn, j);
            betaVector[j + 1] = -sn_currentIteration * betaVector[j];
            betaVector[j] = cs_currentIteration * betaVector[j];
            err = std::abs(betaVector[j + 1]) / b_norm;
            err_v.push_back(err);
            if (err <= tolerance) {
                break;
            }
        }
        auto y = H.sliceMatrix(m, m).divisionByVector(slice(betaVector, 0, m));
        auto result = initialState + y * R[m - 1];
        return result;
    };


} //Slae::Solvers

#endif //MY_PROJECT_GMRES_HPP
