// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridLoader.h
// Date: 23/10/2019

#pragma once
#include "fsm/State.h"

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

        virtual void OnEnter() override;



        void ParseFile(const char* filePath, std::stringstream& stream);
    };

}
