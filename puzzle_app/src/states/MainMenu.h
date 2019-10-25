// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: MainMenu.h
// Date: 25/10/2019

#pragma once

#include <Fixtures/Menu.h>
#include "fsm/State.h"

namespace screen {
    enum Options {
        random = 0,
        build = 1,
        load = 2,
        exit = 3
    };

    class MainMenu : public fsm::State {
    public:
        MainMenu();
        ~MainMenu();

    private:
        WinTUI::Menu* m_MainMenu;

        virtual void OnEnter() override;
        virtual void OnExit() override;
    };

}
