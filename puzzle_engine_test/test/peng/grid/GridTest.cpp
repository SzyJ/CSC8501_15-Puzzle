// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine_test
// File: GridTest.cpp
// Date: 22/10/2019

#include <gtest/gtest.h>
#include <peng/grid/Grid.h>

TEST(TestGrid, Test4x4Assignment) {
    Peng::Grid<int> grid;

    int sampleGrid[15] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15
    };
    grid.SetTiles(sampleGrid, 4);

    for (int xInd = 0; xInd < 4; ++xInd) {
        for (int yInd = 0; yInd < 4; ++yInd) {
            if (xInd == 3 && yInd == 3) {
                break;
            }

            // Same Value stored in different memory locations
            ASSERT_EQ(sampleGrid[xInd + (yInd * 4)], *(grid.GetValue(xInd, yInd)));
            ASSERT_NE(sampleGrid + (xInd + (yInd * 4)), grid.GetValue(xInd, yInd));
        }
    }

}
