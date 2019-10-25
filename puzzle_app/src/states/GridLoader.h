// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridLoader.h
// Date: 25/10/2019

#pragma once
#include "fsm/State.h"

#include <peng/grid/Grid.h>
#include <Fixtures/Menu.h>

#include <string>

namespace screen {

    class GridLoader : public fsm::State {
    public:
        GridLoader() = default;
        ~GridLoader() = default;

    private:

        static bool EmptyString(std::string& str);

        static void ParseFile(const char* filePath, std::stringstream& stream);
        static std::string GetUserChosenFile(const char* dirPath);
        static void PrintGridSolutions(Peng::Grid<int>* grid, std::stringstream& stream);


        virtual void OnEnter() override;

    };

}
