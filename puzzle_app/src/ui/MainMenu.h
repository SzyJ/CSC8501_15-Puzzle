// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: MainMenu.h
// Date: 18/10/2019

#pragma once

#include <Fixtures/Menu.h>

namespace ui {

    class MainMenu {
    public:
        MainMenu();
        ~MainMenu();

        void Show();

        int GetLastSelected();

    private:
       WinTUI::Menu* m_MainMenu;

    };

}
