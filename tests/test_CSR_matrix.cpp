//
// Created by alexander on 13.02.2022.
//

#include "gtest/gtest.h"
#include <my_project/sparse/CSR.hpp>

TEST(TestCSR, Test) {

    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 1},
                                                  {0, 2, 2},
                                                  {1, 1, 1},
                                                  {2, 0, 3},
                                                  {2, 2, 1},
                                                  {2, 3, 2},
                                                  {3, 3, 1}};
    Slae::Matrix::CSR<double> TestMatrix(4, 4, Data);


    std::vector<double> cols(TestMatrix.cols());
    cols[0] = 1.;
    cols[1] = 1.;
    cols[2] = 0.;
    cols[3] = 2.;

    std::vector<double> solve(TestMatrix.rows());
    solve[0] = 1.;
    solve[1] = 1.;
    solve[2] = 7.;
    solve[3] = 2.;

    auto res = TestMatrix * cols;

    ASSERT_EQ(solve.size(), res.size()) << "Vectors solve and res are of unequal length";
    for (int i = 0; i < res.size(); ++i) {
        EXPECT_EQ(solve[i], res[i])
                            << "CSR multiple gives another result than correct analitics resullt. CSR multiple result: "
                            << res[i] << " Analitics result: " << solve[i];
    }
}