//
// Created by alexander on 26.03.2022.
//

#include "gtest/gtest.h"
#include "my_project/solvers/MethodCG.hpp"

TEST(TestMethodCG, Test1) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 10.},
                                                  {0,1, 2.},
                                                  {1,0,3.},
                                                  {1, 1, 4.}};

    Slae::Matrix::CSR<double> TestMatrix(2, 2, Data);

    std::vector<double> AnaliticSolve(TestMatrix.cols_number());
    AnaliticSolve[0] = 0.;
    AnaliticSolve[1] = 0.;


    std::vector<double> b(TestMatrix.rows_number());
    b[0] = 0.;
    b[1] = 0.;

    double tao = 10e-12;

    std::vector<double> initialState(TestMatrix.rows_number());
    initialState[0] = 1.;
    initialState[1] = 1.;

    auto res = Slae::Solvers::MethodCG(TestMatrix, b, tao,  initialState);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Method CG gives another result than correct analitics resullt with this tao: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}

TEST(TestMethodCG, Test2) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, -1.},
                                                  {0,1, 0.},
                                                  {1,0,0.},
                                                  {1, 1, 1.}};

    Slae::Matrix::CSR<double> TestMatrix(2, 2, Data);

    std::vector<double> AnaliticSolve(TestMatrix.cols_number());
    AnaliticSolve[0] = 0.;
    AnaliticSolve[1] = 0.;


    std::vector<double> b(TestMatrix.rows_number());
    b[0] = 0.;
    b[1] = 0.;

    double tao = 10e-12;

    std::vector<double> initialState(TestMatrix.rows_number());
    initialState[0] = 1.;
    initialState[1] = 1.;

    auto res = Slae::Solvers::MethodCG(TestMatrix, b, tao,  initialState);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Method CG gives another result than correct analitics resullt with this tao: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}

TEST(TestMethodCG, Test3) {
    std::set<Slae::Triplet::Triplet<double>> Data{{0, 0, 1.},
                                                  {0,1, 1.},
                                                  {1,0,0.},
                                                  {1, 1, 1.}};

    Slae::Matrix::CSR<double> TestMatrix(2, 2, Data);

    std::vector<double> AnaliticSolve(TestMatrix.cols_number());
    AnaliticSolve[0] = 0.;
    AnaliticSolve[1] = 0.;


    std::vector<double> b(TestMatrix.rows_number());
    b[0] = 0.;
    b[1] = 0.;

    double tao = 10e-12;

    std::vector<double> initialState(TestMatrix.rows_number());
    initialState[0] = 1.;
    initialState[1] = 1.;

    auto res = Slae::Solvers::MethodCG(TestMatrix, b, tao,  initialState);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Method CG gives another result than correct analitics resullt with this tao: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}

TEST(TestMethodCG, TestAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA) {

    const int N = 100;
    std::vector<double> AnaliticSolve(N, 0.);
    std::vector<double> b(N, 0);
    std::vector<double> initialState(N, 1.);

    std::vector<double> values;
    values.push_back(100.);
    values.push_back(99.);
    double s = 2.;
    for (int i = 0; i < 98; ++i) {
        values.push_back(s);
        s -= 1. / 98;
    }
    std::vector<std::size_t> colums;
    std::vector<std::size_t> rows;
    for (std::size_t i = 0; i < 100; ++i) {
        colums.push_back(i);
        rows.push_back(i);
    }

    Slae::Matrix::CSR<double> TestMatrix(N, N, values, colums, rows);

    double tao = 10e-12;

    auto res = Slae::Solvers::MethodCG(TestMatrix, b, tao, initialState);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Method CG gives another result than correct analitics resullt with this tao: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}

TEST(TestMethodCG, TestAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa) {

    const int N = 100;
    std::vector<double> AnaliticSolve(N, 0.);
    std::vector<double> b(N, 0);
    std::vector<double> initialState(N, 1.);

    std::vector<double> values;
    for (int i = 100; i > 0 ; --i) {
        values.push_back(i);
    }
    std::vector<std::size_t> colums;
    std::vector<std::size_t> rows;
    for (std::size_t i = 0; i < 100; ++i) {
        colums.push_back(i);
        rows.push_back(i);
    }

    Slae::Matrix::CSR<double> TestMatrix(N, N, values, colums, rows);

    double tao = 10e-12;

    auto res = Slae::Solvers::MethodCG(TestMatrix, b, tao, initialState);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Method CG gives another result than correct analitics resullt with this tao: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}