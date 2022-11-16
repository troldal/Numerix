//
// Created by Kenneth Balslev on 16/10/2022.
//

#include <iostream>
#include <algorithm>
#include <linalg/GaussJordan.h>
#include <linalg/Matrix.hpp>

int main()
{
    numerix::linalg::Matrix<int> m1(4, 4);

    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[0][3] = 4;

    m1[1][0] = 5;
    m1[1][1] = 6;
    m1[1][2] = 7;
    m1[1][3] = 8;

    m1[2][0] = 9;
    m1[2][1] = 10;
    m1[2][2] = 11;
    m1[2][3] = 12;

    m1[3][0] = 13;
    m1[3][1] = 14;
    m1[3][2] = 15;
    m1[3][3] = 16;

    std::cout << m1 <<std::endl;

    auto item = std::find(m1.begin(), m1.end(), 16);

    auto m2 = m1({0,1,1}, {0,4,1});
    std::cout << m2 <<std::endl;

    auto m3 = m1({0,4,1}, {0,1,1});
    std::cout << m3 <<std::endl;

    auto m4 = m1({1,3,1}, {1,3,1});
    std::cout << m4 <<std::endl;

    auto m5 = m4({0,2,2}, {0,2,2});
    std::cout << m5 <<std::endl;
    for (auto elem : m5) std::cout << elem << std::endl;

    auto m6 = m5({0,2,1}, {0,1,1});
    std::cout << m6 <<std::endl;
    for (auto& elem : m6) std::cout << elem << std::endl;

    auto m7 = m5({0,2,1}, {1,1,1});
    std::cout << m7 <<std::endl;
    for (auto& elem : m7) std::cout << elem << std::endl;

    auto m8 = m5({0,1,1}, {0,2,1});
    std::cout << m8 <<std::endl;
    for (auto& elem : m8) std::cout << elem << std::endl;

    auto m9 = m5({1,1,1}, {0,2,1});
    std::cout << m9 <<std::endl;
    for (auto& elem : m9) std::cout << elem << std::endl;
}

//int main() {
//
//    numerix::linalg::Matrix<double> m1(4,4);
//
//    m1[0][0] = 0.18;
//    m1[0][1] = 0.60;
//    m1[0][2] = 0.57;
//    m1[0][3] = 0.96;
//
//    m1[1][0] = 0.41;
//    m1[1][1] = 0.24;
//    m1[1][2] = 0.99;
//    m1[1][3] = 0.58;
//
//    m1[2][0] = 0.14;
//    m1[2][1] = 0.30;
//    m1[2][2] = 0.97;
//    m1[2][3] = 0.66;
//
//    m1[3][0] = 0.51;
//    m1[3][1] = 0.13;
//    m1[3][2] = 0.19;
//    m1[3][3] = 0.85;
//
//    numerix::linalg::Matrix<double> m2(4,1);
//    m2[0][0] = 1.0;
//    m2[1][0] = 2.0;
//    m2[2][0] = 3.0;
//    m2[3][0] = 4.0;
//
//    std::cout << m2 << std::endl;
//
//    auto m3 = m1 * m2;
//    std::cout << m3 << std::endl;
//
////    numerix::linalg::Matrix<double> m2(4,1);
////    m2[0][0] = 1.0;
////    m2[1][0] = 2.0;
////    m2[2][0] = 3.0;
////    m2[3][0] = 4.0;
////
////
////    //m2.print();
////
////    auto m3 = numerix::linalg::GaussJordan(m1, m2);
////    m3.print();
////
////    auto m4 = m1 * m3;
////    m4.print();
//
//    auto slice = numerix::linalg::MatrixSlice(0, {3,2}, {3,1});
//
//    std::cout << slice(0,0) << std::endl;
//    std::cout << slice(0,1) << std::endl;
//    std::cout << slice(1,0) << std::endl;
//    std::cout << slice(1,1) << std::endl;
//    std::cout << slice(2,0) << std::endl;
//    std::cout << slice(2,1) << std::endl << std::endl;
//
//    auto sl = numerix::linalg::Slice(0,-1,3);
//    std::cout << sl(0) << std::endl;
//    std::cout << sl(1) << std::endl;
//    std::cout << sl(2) << std::endl;
//
//    std::cout << m1 << std::endl;
//
//    auto m5 = m1({2,2,1}, {2,2,1});
//    std::cout << m5 << std::endl;
//
//    m1(0,0) = 1.42;
//    std::cout << m1 << std::endl;
//    std::cout << m1(0,0) << std::endl;
//
//
//    const auto mx = m1;
//    std::cout << mx(0,0) << std::endl;
//    auto val = mx(0,0);
//
//    numerix::linalg::Matrix<double> x1(2,2);
//
//    x1[0][0] = 1;
//    x1[0][1] = 2;
//    x1[1][0] = 3;
//    x1[1][1] = 4;
//
//    numerix::linalg::Matrix<double> x2(2,2);
//
//    x2[0][0] = 1;
//    x2[0][1] = 2;
//    x2[1][0] = 3;
//    x2[1][1] = 4;
//
//    std::cout << x1 << std::endl;
//    x1 += 1;
//    std::cout << x1 << std::endl;
//
//    for (auto& item : m5) item = 0.0;
//    m5 += x1;
//    std::cout << m1;
//
//    auto l1 = m1({0,4,4}, {0,2,1});
//    std::cout << l1 << std::endl;
//    auto l2 = l1({0,4,2}, {1,1,1});
//    std::cout << l2 << std::endl;
//
//
//    return 0;
//}