//
// Created by alexander on 11.02.2022.
//

#include "gtest/gtest.h"
#include <my_project/SlaeBaseException.hpp>
#include <my_project/solvers/ThreeDiagonalSolver.hpp>

TEST(TestThreeDiagonalSolver, test1) {

    Slae::Matrix::ThreeDiagonalMatrix TestFirstMatrix(4);
    TestFirstMatrix(0, 0) = 1.;
    TestFirstMatrix(0, 1) = 1.;
    TestFirstMatrix(1,0) = 0.;
    TestFirstMatrix(1, 1) = 1.;
    TestFirstMatrix(1, 2) = 0.;
    TestFirstMatrix(2, 0) = 0.;
    TestFirstMatrix(2, 1) = 1.;
    TestFirstMatrix(2, 2) = 0.;
    TestFirstMatrix(3, 0) = 0.;
    TestFirstMatrix(3, 1) = 0.;
    TestFirstMatrix(3, 2) = 1.;

    std::vector<double> cols(TestFirstMatrix.rows());
    cols[0] = 1.;
    cols[1] = 2.;
    cols[2] = 1.;
    cols[3] = 2.;

    std::vector<double> solve(TestFirstMatrix.rows());
    solve[0] = -1.;
    solve[1] = 2.;
    solve[2] = 1.;
    solve[3] = 2.;
    auto res = Slae::Solvers::solveThreeDiagonal(TestFirstMatrix, cols);

    ASSERT_EQ(solve.size(), res.size()) << "Vectors solve and res are of unequal length";
    for (int i = 0; i < res.size(); ++i) {
        EXPECT_EQ(solve[i], res[i]) << "RunThroughMethod gives another result than correct analitics resullt. RunThroughMethod result: " << solve[i] << " Analitics result: " << res[i];
    }
}