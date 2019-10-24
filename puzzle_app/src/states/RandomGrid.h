// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: RandomGrid.h
// Date: 22/10/2019

#pragma once
#include "fsm/State.h"

#include <peng/grid/Grid.h>
#include <Fixtures/Prompt.h>
#include <Fixtures/Menu.h>

namespace screen {

    class RandomGrid : public fsm::State {
    public:
        RandomGrid();
        ~RandomGrid();

    private:
        WinTUI::Prompt* m_NumberPrompt;
        WinTUI::Menu* m_FileSelector;

        int GetUserChoice();

        static void GenerateGrid(Peng::Grid<int>& tileGrid, int numbersFrom, int numbersTo);

        void GenerateAndPrintGrids(std::stringstream& stream, int generateCount, int numberFrom, int numberTo);
        virtual void OnEnter() override;

    };

}
