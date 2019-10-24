// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: EntryPoint.cpp
// Date: 21/10/2019

#include "fsm/Controller.h"

#include <peng/grid/GridSolver.h>

int main() {

    fsm::Controller::Get().Start(fsm::States::MainMenu);


    //Peng::Grid<int> grid;
    //
    //int tileArray[15] = {
    //    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
    //};
    //
    //grid.SetTiles(tileArray, 4);
    //
    //std::cout << "Grid Solutions: " << Peng::GridSolver::CountAll<int>(grid);

    return 0;
}
