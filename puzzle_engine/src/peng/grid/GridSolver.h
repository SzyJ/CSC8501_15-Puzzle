// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: GridSolver.h
// Date: 24/10/2019

#pragma once
#include "peng/grid/Grid.h"
#include "peng/math/Math.h"

namespace Peng {

    class GridSolver {
    public:
        template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
        static void CountAll(const Grid<T>& grid, const unsigned int sequenceLength, unsigned long long& horizontalSeq, unsigned long long& verticalSeq) {
            unsigned int width; // Width of the grid
            unsigned int height; // Height of the grid
            unsigned int sequenceLen; // Sequence Length
            unsigned int subsequenceCombinations; // Ways of making the sequence
            unsigned long long arrangements; // Ways of arranging remaining tiles
            unsigned int ah; // Available places horizontally
            unsigned int av; // Available places vertically

            width = grid.GetWidth();
            height = grid.GetHeight();
            sequenceLen = sequenceLength;
            subsequenceCombinations = grid.GetSubsequenceCombinations(sequenceLength);
            arrangements = static_cast<unsigned long long>(Math::Factorial(((width * height) - 1) - sequenceLen) / 2);

            // Horizontal places
            if (sequenceLen == width) {
                ah = height - 1;
            } else if (sequenceLen < width) {
                ah = ((width - sequenceLen + 1) * (height - 1)) + (width - sequenceLen);
            } else {
                ah = 0;
            }

            // Vertical places
            if (sequenceLen == height) {
                av = width - 1;
            } else if (sequenceLen < height) {
                av = ((height - sequenceLen + 1) * (width - 1)) + (height - sequenceLen);
            } else {
                av = 0;
            }

            horizontalSeq = ah * arrangements * subsequenceCombinations;
            verticalSeq = av * arrangements * subsequenceCombinations;
        }

        template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
        static void CountThis(const Grid<T>& grid, const unsigned int sequenceLength, unsigned long& total) {
            unsigned int width; // Width of the grid
            unsigned int height; // Height of the grid

            width = grid.GetWidth();
            height = grid.GetHeight();

            total = 0;

            T lastVal = -1;

            unsigned int currentSequence = 1;

            for (unsigned int gridY = 0; gridY < height; ++gridY) {
                for (unsigned int gridX = 0; gridX < width; ++gridX) {
                    if (gridY == height - 1 && gridX == width - 1) {
                        break;
                    }

                    if (lastVal < 0) {
                        lastVal = grid.GetValue(gridX, gridY);
                        continue;
                    }

                    T thisVal;
                    if ((thisVal = grid.GetValue(gridX, gridY)) == lastVal + 1 || thisVal == lastVal - 1) {
                        ++currentSequence;
                        lastVal = thisVal;
                    } else {
                        if (currentSequence >= sequenceLength) {
                            total += currentSequence - sequenceLength + 1;
                        }
                        currentSequence = 1;
                        lastVal = thisVal;
                    }
                }

                if (currentSequence >= sequenceLength) {
                    total += currentSequence - sequenceLength + 1;
                }
                currentSequence = 1;

                lastVal = -1;
            }

            for (unsigned int gridX = 0; gridX < width; ++gridX) {
                for (unsigned int gridY = 0; gridY < height; ++gridY) {
                    if (gridX == width - 1 && gridY == height - 1) {
                        break;
                    }

                    if (lastVal < 0) {
                        lastVal = grid.GetValue(gridX, gridY);
                        continue;
                    }

                    int thisVal;
                    if ((thisVal = grid.GetValue(gridX, gridY)) == lastVal + 1 || thisVal == lastVal - 1) {
                        ++currentSequence;
                        lastVal = thisVal;
                    } else {
                        if (currentSequence >= sequenceLength) {
                            total += currentSequence - sequenceLength + 1;
                        }
                        currentSequence = 1;
                        lastVal = thisVal;
                    }
                }

                if (currentSequence >= sequenceLength) {
                    total += currentSequence - sequenceLength + 1;
                }
                currentSequence = 1;

                lastVal = -1;
            }

        }

    };

}
