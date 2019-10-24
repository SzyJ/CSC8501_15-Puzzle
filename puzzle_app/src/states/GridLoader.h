// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridLoader.h
// Date: 23/10/2019

#pragma once
#include "fsm/State.h"

#include <peng/grid/Grid.h>
#include <Fixtures/Menu.h>

#include <string>

namespace screen {

    class GridLoader : public fsm::State {
    public:
        GridLoader();
        ~GridLoader();

    private:
        WinTUI::Menu* m_PrintToFileMenu;

        static bool EmptyString(std::string& str);

        void ParseFile(const char* filePath, std::stringstream& stream) const;
        static std::string GetUserChosenFile(const char* dirPath);
        static void PrintGridSolutions(Peng::Grid<int>* grid, std::stringstream& stream);


        virtual void OnEnter() override;

    };

}
