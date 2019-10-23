// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: GridSolver.h
// Date: 23/10/2019

#pragma once
#include "peng/grid/Grid.h"
#include "peng/math/Math.h"


namespace Peng {

    class GridSolver {

    public:
        template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
        static unsigned long long Do(const Grid<T>& grid) {
            unsigned long long z; // Ways of arranging unused tiles
            unsigned int u; // Ways of choosing a sequence
            unsigned int q; // Ways of reversing a collection of sequences
            unsigned int x; // Ways of arranging the sequences
            unsigned int m; // No. of rows/cols where sequence could be

            int size = grid.GetSize();
            int sequenceLength = size;
            int tileCount = (size * size) - 1;

            unsigned long long count = 0;

            for (int sequenceCount = 1; sequenceCount < grid.GetSize(); ++sequenceCount) {
                z = static_cast<unsigned long long>(0.5 * Math::Factorial( tileCount - (sequenceCount * sequenceLength)));
                u = Math::Combination((tileCount - sequenceCount * sequenceLength) + sequenceCount, sequenceCount);
                q = static_cast<unsigned int>(sequenceCount * Math::Pow2(sequenceCount) * 0.5);
                x = Math::Factorial(sequenceCount);
                m = Math::Combination(size - 1, sequenceCount);


                count += z * u * q * x * m;
            }

            return count;
        }

    };

}
