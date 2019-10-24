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
        static void Do(const Grid<T>& grid, const unsigned int sequenceLength, unsigned long& horizontalSeq, unsigned long& verticalSeq) {
            unsigned int w; // Width of the grid
            unsigned int h; // Height of the grid
            unsigned int s; // Sequence Length
            unsigned int c; // Ways of making the sequence
            unsigned long long r; // Ways of arranging remaining tiles
            unsigned int ah; // Available places horizontally
            unsigned int av; // Available places vertically

            w = grid.GetWidth();
            h = grid.GetHeight();
            s = sequenceLength;
            c = grid.GetSubsequenceCombinations(sequenceLength);
            r = static_cast<unsigned long long>(Math::Factorial(((w * h) - 1) - s) / 2);

            // Horizontal places
            if (s == w) {
                ah = h - 1;
            } else if (s < w) {
                ah = ((w - s + 1) * (h - 1)) + (w - s);
            } else {
                ah = 0;
            }

            // Vertical places
            if (s == h) {
                av = w - 1;
            } else if (s < h) {
                av = ((h - s + 1) * (w - 1)) + (h - s);
            } else {
                av = 0;
            }

            horizontalSeq = ah * r * c;
            verticalSeq = av * r * c;
        }

    };

}
