//
// Created by alexander on 12.03.2022.
//

#include "gtest/gtest.h"
#include "my_project/solvers/GaussSeidel.hpp"

TEST(TestFastGaussZeidel, Test) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 2},
                                                  {0, 1, 1},
                                                  {1, 0, 1},
                                                  {1, 2, 1},
                                                  {2, 1, 1},
                                                  {2, 3, 1},
                                                  {3, 2, 1},
                                                  {1, 1, 2},
                                                  {2, 2, 2},
                                                  {3, 3, 2},
                                                  {4, 4, 2},
                                                  {4, 3, 1},
                                                  {3, 4, 1}};
    Slae::Matrix::CSR<double> TestMatrix(5, 5, Data);

    std::vector<double> AnaliticSolve(5, 0);
    AnaliticSolve[0] = 0.;
    AnaliticSolve[1] = 0.;
    AnaliticSolve[2] = 0.;
    AnaliticSolve[3] = 0.;
    AnaliticSolve[4] = 0.;

    std::vector<double> b(TestMatrix.rows_number());
    b[0] = 0.;
    b[1] = 0.;
    b[2] = 0.;
    b[3] = 0.;
    b[4] = 0.;
    b[5] = 0.;

    std::vector<double> InitialState(TestMatrix.rows_number());
    InitialState[0] = 100.;
    InitialState[1] = 100.;
    InitialState[2] = 100.;
    InitialState[3] = 100.;
    InitialState[4] = 100.;

    double Tolerance = 1e-25;

    auto res = Slae::Solvers::FastGaussSeidel(TestMatrix, b, InitialState, 0.75, Tolerance);
    ASSERT_EQ(AnaliticSolve.size(), res.size()) << "Vectors solve and res are of unequal length";
    for (int i = 0; i < res.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Gauss-Zeidel gives another result than correct analitics resullt with this tolerance: "
                            << Tolerance << ".  Gauss_Zeidel method result: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}