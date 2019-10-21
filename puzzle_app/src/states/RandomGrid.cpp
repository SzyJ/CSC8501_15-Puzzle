// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: RandomGrid.cpp
// Date: 21/10/2019

#include "RandomGrid.h"
#include "Utils/Color.h"

#include <cctype>
#include <cmath>

#define GET_DIGITS(x) floor(log10(x))
#define MAX_GRID_COUNT 5


namespace screen {

    RandomGrid::RandomGrid() {
        m_NumberPrompt = new WinTUI::Prompt("How many grids to generate");

        m_NumberPrompt->SetSelectedBefore([](std::ostream& ostream) {
            WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN);
            });
        m_NumberPrompt->SetSelectedAfter([](std::ostream& ostream) {
            WinTUI::Color::ResetConsoleColor();
            ostream << "? ";
            });
        m_NumberPrompt->SetCondition([](const char* string) {
            char thisChar;

            for (int cIndex = 0; (thisChar = string[cIndex]) != '\0'; ++cIndex) {
                if (!std::isdigit(thisChar)) {
                    return false;
                }

                if (cIndex > GET_DIGITS(MAX_GRID_COUNT)) {
                    return false;
                }
            }

            return true;
            });
        m_NumberPrompt->SetWarning([](std::ostream& ostream) {
            WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
            ostream << "Only enter " << (GET_DIGITS(MAX_GRID_COUNT) + 1) << " or less number characters" << std::endl;
            });
    }


    RandomGrid::~RandomGrid() {
        delete m_NumberPrompt;
    }


    int RandomGrid::GetUserChoice() {
        m_NumberPrompt->Show(std::cout);
        return 0;
    }
    
    void RandomGrid::OnEnter() {
        GetUserChoice();
    }

}
