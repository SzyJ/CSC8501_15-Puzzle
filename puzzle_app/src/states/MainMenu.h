// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: MainMenu.h
// Date: 18/10/2019

#pragma once

#include <Fixtures/Menu.h>
#include "fsm/State.h"

namespace ui {
    enum Options {
        build,
        load,
        exit
    };

    class MainMenu : public fsm::State {
    public:
        MainMenu();
        ~MainMenu();

        void Show();

        int GetLastSelected();

        void GoTo();

    private:
       WinTUI::Menu* m_MainMenu;

       void OnEnter() override;
    };

}
