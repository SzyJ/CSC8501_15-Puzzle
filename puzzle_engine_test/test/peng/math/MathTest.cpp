// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine_test
// File: MathTest.cpp
// Date: 17/10/2019

#include "gtest/gtest.h"
#include "peng/math/Math.h"

TEST(testMath, FactorialTest) {
    EXPECT_EQ(6, WinTUI::Math::Factorial(3));
    EXPECT_EQ(1, WinTUI::Math::Factorial(0));
    EXPECT_EQ(1, WinTUI::Math::Factorial(1));

}

TEST(testMath, CombinationTest) {
    EXPECT_EQ(15, WinTUI::Math::Combination(6,2));
    EXPECT_EQ(0, WinTUI::Math::Combination(6,15));
    EXPECT_EQ(1, WinTUI::Math::Combination(10,10));
}
