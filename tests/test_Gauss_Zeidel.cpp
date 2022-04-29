//
// Created by alexander on 23.02.2022.
//

#include "gtest/gtest.h"
#include "my_project/solvers/GaussSeidel.hpp"

TEST(TestGaussZeidel, Test) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 7},
                                                  {0, 1, 1},
                                                  {1, 0, 1},
                                                  {1, 2, 1},
                                                  {2, 1, 1},
                                                  {2, 3, 1},
                                                  {3, 2, 1},
                                                  {1, 1, 7},
                                                  {2, 2, 7},
                                                  {3, 3, 7}};
    Slae::Matrix::CSR<double> TestMatrix(4, 4, Data);

    std::vector<double> AnaliticSolve(TestMatrix.cols_number());
    AnaliticSolve[0] = 14. / 55;
    AnaliticSolve[1] = 12. / 55;
    AnaliticSolve[2] = 12. / 55;
    AnaliticSolve[3] = 14. / 55;

    std::vector<double> b(TestMatrix.rows_number());
    b[0] = 2.;
    b[1] = 2.;
    b[2] = 2.;
    b[3] = 2.;

    std::vector<double> InitialState(TestMatrix.rows_number());
    InitialState[0] = 0.;
    InitialState[1] = 0.;
    InitialState[2] = 0.;
    InitialState[3] = 0.;

    double Tolerance = 0.87;

    auto res = Slae::Solvers::GaussSeidel(TestMatrix, b, InitialState, Tolerance);
    ASSERT_EQ(AnaliticSolve.size(), res.size()) << "Vectors solve and res are of unequal length";
    for (int i = 0; i < res.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Gauss-Zeidel gives another result than correct analitics resullt with this tolerance: "
                            << Tolerance << ".  Gauss_Zeidel method result: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}