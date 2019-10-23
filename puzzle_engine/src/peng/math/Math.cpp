// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: Math.cpp
// Date: 17/10/2019

#include "Math.h"

namespace Peng {

    int Math::Factorial(int number) {
        if (number <= 1) {
            return 1;
        }

        if (number == 2) {
            return 2;
        }

        return number * Factorial(number - 1);
    }

    int Math::Combination(int n, int r) {
        int val = 0;

        if (n == r) {
            return 1;
        }
        if (n < r) {
            return 0;
        }

        return Factorial(n) / (Factorial(r) * Factorial(n - r));
    }

    int Math::Pow2(int pow) {
        return (1 << pow);
    }

}
