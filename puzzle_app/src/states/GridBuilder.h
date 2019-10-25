// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridBuilder.h
// Date: 25/10/2019

#pragma once

#include "fsm/State.h"
#include <Fixtures/Matrix.h>
#include <Fixtures/Prompt.h>
#include <Fixtures/Menu.h>

namespace screen {

    class GridBuilder : public fsm::State {
    public:
        GridBuilder();
        ~GridBuilder();

    private:
        std::string prompt;

        WinTUI::Prompt* m_MatrixInput = nullptr;

        WinTUI::Matrix<int>* m_GridBuilder = nullptr;

        static bool ValidateGridMatrix(int* array, int length, std::stringstream& info);

        inline void ConfigureMatrixPrompt();
        inline void ConfigureGridBuilder();

        virtual void OnEnter() override;
    };

}
