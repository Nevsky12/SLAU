//
// Created by alexander on 23.04.22.
//

#include "gtest/gtest.h"
#include "my_project/solvers/GMRES.hpp"


TEST(TestGMRES, Test) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 10.},
                                                  {0, 1, -9.},
                                                  {1, 0, -9.},
                                                  {1, 1, 10.}};

    DenseMatrix<double> TestMatrix(2, 2, Data);

    std::vector<double> AnaliticSolve(TestMatrix.sizeH());
    AnaliticSolve[0] = 5.;
    AnaliticSolve[1] = 6.;

    std::vector<double> b(TestMatrix.sizeW());
    b[0] = -4.;
    b[1] = 15.;

    std::vector<double> initialState(TestMatrix.sizeW());
    initialState[0] = 11.;
    initialState[1] = 0.;


    auto res = Slae::Solvers::GMRES(TestMatrix, b, initialState, 10e-12, 7);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "GMRES gives another result than correct analitics resullt "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}