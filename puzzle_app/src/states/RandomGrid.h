// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: RandomGrid.h
// Date: 25/10/2019

#pragma once
#include "fsm/State.h"

#include <peng/grid/Grid.h>
#include <Fixtures/Prompt.h>
#include <Fixtures/Menu.h>

namespace screen {

    class RandomGrid : public fsm::State {
    public:
        RandomGrid() = default;
        ~RandomGrid() = default;

    private:
        static WinTUI::Prompt* GetNumberPrompt();

        static int GetUserChoice();

        static void GenerateGrid(Peng::Grid<int>& tileGrid, int numbersFrom, int numbersTo);

        static void GenerateAndPrintGrids(std::stringstream& stream, int generateCount, int numberFrom, int numberTo);
        virtual void OnEnter() override;

    };

}
