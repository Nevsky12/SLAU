//
// Created by alexander on 24.02.2022.
//
#include "gtest/gtest.h"
#include "my_project/solvers/SimpleIteration.hpp"

TEST(TestSimpleIteration, Test) {
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

    double tao = 0.1;

    auto res = Slae::Solvers::SimpleIteration(TestMatrix, b, tao);
    ASSERT_EQ(AnaliticSolve.size(), res.size()) << "Vectors solve and res are of unequal length";
    for (int i = 0; i < res.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Simple iteration method gives another result than correct analitics resullt with this tao: "
                            << tao << ".  Simple iteration method result: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}