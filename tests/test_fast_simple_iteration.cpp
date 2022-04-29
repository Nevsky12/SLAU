//
// Created by alexander on 19.03.2022.
//
#include "gtest/gtest.h"
#include "my_project/solvers/FastSimpleIteration.hpp"

TEST(TestFastSimpleIteration1, Test1) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 10.},
                                                  {0, 1, -9.},
                                                  {1, 0, -9.},
                                                  {1, 1, 10.}};
    std::set<Slae::Triplet::Triplet<double>> Data_reverse{{0, 0, 10. / 19},
                                                          {0, 1, 9. / 10},
                                                          {1, 0, 9. / 19},
                                                          {1, 1, 10. / 19}};
    Slae::Matrix::CSR<double> TestMatrix(2, 2, Data);
    Slae::Matrix::CSR<double> TestMatrix_reverse(2, 2, Data_reverse);

    std::vector<double> AnaliticSolve(TestMatrix.cols_number());
    AnaliticSolve[0] = 5.;
    AnaliticSolve[1] = 6.;

    std::vector<double> b(TestMatrix.rows_number());
    b[0] = -4.;
    b[1] = 15.;

    std::vector<double> initialState(TestMatrix.rows_number());
    initialState[0] = 11.;
    initialState[1] = 0.;

    std::pair<double, double> section = {1., 19.};

    auto res = Slae::Solvers::FastSimpleIteration<double, 16>(TestMatrix, TestMatrix_reverse, b, initialState, section);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Fast simple iteration gives another result than correct analitics resullt "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}

TEST(TestFastSimpleIteration2, Test2) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 10.},
                                                  {0,1, -18.},
                                                  {0,2,2.},
                                                  {1, 0, -18.},
                                                  {1, 1, 40.},
                                                  {1,2,-1.},
                                                  {2,0,2.},
                                                  {2,1,-1.},
                                                  {2,2,3.}};
    std::set<Slae::Triplet::Triplet<double>> Data_reverse{{0, 0, 119. / 130},
                                                          {0,1, 2. / 5},
                                                          {0,2,-31. / 65},
                                                          {1, 0, 2. / 5},
                                                          {1, 1, 1. / 5},
                                                          {1,2,-1. / 5},
                                                          {2,0,-31. / 65},
                                                          {2,1,-1. / 5},
                                                          {2,2,38. / 65}};
    Slae::Matrix::CSR<double> TestMatrix(3, 3, Data);
    Slae::Matrix::CSR<double> TestMatrix_reverse(3, 3, Data_reverse);

    std::vector<double> AnaliticSolve(TestMatrix.cols_number());
    AnaliticSolve[0] = 4.;
    AnaliticSolve[1] = 3.;
    AnaliticSolve[2] = 1.;


    std::vector<double> b(TestMatrix.rows_number());
    b[0] = -12.;
    b[1] = 47.;
    b[2] = 8.;

    std::pair<double, double> section = {0.706,  48.498};

    std::vector<double> initialState(TestMatrix.rows_number());
    initialState[0] = 4.46;
    initialState[1] = 2.25;
    initialState[2] = 1.85;

    auto res = Slae::Solvers::FastSimpleIteration<double, 16>(TestMatrix, TestMatrix_reverse, b, initialState, section);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Steepest gradient method gives another result than correct analitics resullt with this tao: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}

TEST(TestSimpleIteration, Test3) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 9.},
                                                  {0,1, 8.},
                                                  {1,0,8.},
                                                  {1, 1, 9.}};
    std::set<Slae::Triplet::Triplet<double>> Data_reverse{{0, 0, 9. / 17},
                                                          {0,1, -8. / 17},
                                                          {1,0, -8. / 17},
                                                          {1, 1, 9. / 17}};

    Slae::Matrix::CSR<double> TestMatrix(2, 2, Data);
    Slae::Matrix::CSR<double> TestMatrix_reverse(2, 2, Data_reverse);

    std::vector<double> AnaliticSolve(TestMatrix.cols_number());
    AnaliticSolve[0] = 1. / 17;
    AnaliticSolve[1] = 1. / 17;


    std::vector<double> b(TestMatrix.rows_number());
    b[0] = 1.;
    b[1] = 1.;

    double tao = 10e-12;

    std::vector<double> initialState(TestMatrix.rows_number());
    initialState[0] = 10.;
    initialState[1] = 5.;

    std::pair<double, double> section = {1.,  17.};

    auto res = Slae::Solvers::FastSimpleIteration<double, 16>(TestMatrix, TestMatrix_reverse, b, initialState, section);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Method CG gives another result than correct analitics resullt with this tao: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}
