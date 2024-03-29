// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine_test
// File: MathTest.cpp
// Date: 17/10/2019

#include "gtest/gtest.h"
#include "peng/math/Math.h"

TEST(TestMath, FactorialTest) {
    EXPECT_EQ(6, Peng::Math::Factorial(3));
    EXPECT_EQ(1, Peng::Math::Factorial(0));
    EXPECT_EQ(1, Peng::Math::Factorial(1));
    EXPECT_EQ(2, Peng::Math::Factorial(2));
}

TEST(TestMath, CombinationTest) {
    EXPECT_EQ(15, Peng::Math::Combination(6,2));
    EXPECT_EQ(0,  Peng::Math::Combination(6,15));
    EXPECT_EQ(1,  Peng::Math::Combination(10,10));
}

TEST(TestMath, Pow2Test) {
    EXPECT_EQ(16, Peng::Math::Pow2(4));
    EXPECT_EQ(8, Peng::Math::Pow2(3));
    EXPECT_EQ(4, Peng::Math::Pow2(2));
    EXPECT_EQ(2, Peng::Math::Pow2(1));
    EXPECT_EQ(1, Peng::Math::Pow2(0));
}
