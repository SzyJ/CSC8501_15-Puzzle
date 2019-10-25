// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: MainMenu.cpp
// Date: 25/10/2019

#include "MainMenu.h"
#include "fsm/Controller.h"
#include "Utils/Color.h"
#include "Utils/Console.h"

#include <iostream>

namespace screen {

    MainMenu::MainMenu() {
        const char* m_MenuOptions[] = {
            "Generate random grid",
            "Create a custom grid",
            "   Load from file   ",
            "        Exit        "
        };

        m_MainMenu = new WinTUI::Menu(m_MenuOptions, 4);

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

    void MainMenu::OnEnter() {
        m_MainMenu->Show(std::cout);

        switch (m_MainMenu->GetLastSelected()) {
        case random:
            fsm::Controller::Get().GoTo(fsm::States::RandomGrid);
            break;
        case build:
            fsm::Controller::Get().GoTo(fsm::States::GridBuilder);
            break;
        case load:
            fsm::Controller::Get().GoTo(fsm::States::GridLoader);
            break;
        case exit:
        default:
            break;
        }

    }

    void MainMenu::OnExit() {
        WinTUI::Console::ClearScreen();
    }

}
