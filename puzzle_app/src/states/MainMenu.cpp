// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: MainMenu.cpp
// Date: 18/10/2019

#include "Utils/Color.h"
#include "MainMenu.h"
#include <iostream>

namespace ui {

    void MainMenu::OnEnter() {
        Show();
    }

    MainMenu::MainMenu() {
        const char* m_MenuOptions[] = {
           "Create a custom grid",
           "   Load from file   ",
           "        Exit        "
        };

        m_MainMenu = new WinTUI::Menu(m_MenuOptions, 3);

        m_MainMenu->SetSelectedBefore([](std::ostream& ostream) {
            ostream << "* ";
            WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN);
            });
        m_MainMenu->SetSelectedAfter([](std::ostream& ostream) {
            WinTUI::Color::ResetConsoleColor();
            ostream << " *";
            });

        m_MainMenu->SetUnselectedBefore([](std::ostream& ostream) {
            ostream << "  ";
            });

        m_MainMenu->SetUnselectedAfter([](std::ostream& ostream) {
            ostream << "  ";
            });
    }

    MainMenu::~MainMenu() {
        delete m_MainMenu;
    }

    void MainMenu::Show() { m_MainMenu->Show(std::cout); }

    int MainMenu::GetLastSelected() { return m_MainMenu->GetLastSelected(); }

}
