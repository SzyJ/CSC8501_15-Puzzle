// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: RandomGrid.cpp
// Date: 25/10/2019

#include "RandomGrid.h"
#include "Utils/Color.h"
#include "fsm/Controller.h"
#include <peng/math/Random.h>
#include <Utils/Keyboard.h>

#include <cctype>
#include <cmath>
#include <sstream>
#include <fileio/FileWriter.h>

#define GET_DIGITS(x) ((int) floor(log10(x)))
#define MAX_GRID_COUNT 99999
#define GRID_SIZE 4

#define DEFAULT_FILENAME "random_puzzle.15f"


namespace screen {

    WinTUI::Prompt* RandomGrid::GetNumberPrompt() {
        auto* numberPrompt = new WinTUI::Prompt("How many grids to generate");

        numberPrompt->SetSelectedBefore([](std::ostream& ostream) {
            WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN);
        });
        numberPrompt->SetSelectedAfter([](std::ostream& ostream) {
            WinTUI::Color::ResetConsoleColor();
            ostream << "? ";
        });
        numberPrompt->SetCondition([](const char* string) {
            char thisChar;

            if (*string == '\0') {
                return false;
            }

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
        numberPrompt->SetWarning([](std::ostream& ostream) {
            WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
            int expectedNum = (GET_DIGITS(MAX_GRID_COUNT) + 1);

            ostream << "Only enter " << expectedNum;

            if (expectedNum > 1) {
                ostream << " or less number characters" << std::endl;
            } else {
                ostream << " number character" << std::endl;
            }

        });

        return numberPrompt;
    }

    int RandomGrid::GetUserChoice() {
        WinTUI::Prompt* numberPrompt = GetNumberPrompt();
        int gridsToGenerate;

        do {
            numberPrompt->Show(std::cout);
        } while ((gridsToGenerate = std::stoi(numberPrompt->GetLastResponse())) > MAX_GRID_COUNT);

        delete numberPrompt;
        return gridsToGenerate;
    }

    void RandomGrid::GenerateGrid(Peng::Grid<int>& tileGrid, int numbersFrom, int numbersTo) {
        const unsigned int tileCount = (GRID_SIZE * GRID_SIZE) - 1;

        Peng::RandomSession rngSession(numbersFrom, numbersTo);

        int tileArray[tileCount];
        for (int& tile : tileArray) {
            tile = rngSession.GetNew();
        }

        tileGrid.SetTiles(tileArray, GRID_SIZE);
    }

    void RandomGrid::GenerateAndPrintGrids(std::stringstream& stream, int generateCount, int numberFrom, int numberTo) {
        stream << generateCount << std::endl;

        for (int i = 0; i < generateCount; ++i) {
            Peng::Grid<int> tileGrid;
            GenerateGrid(tileGrid, numberFrom, numberTo);
            stream << tileGrid;
            stream << std::endl;
        }

    }

    void RandomGrid::OnEnter() {
        int gridCount = GetUserChoice();
        std::stringstream stream;
        GenerateAndPrintGrids(stream, gridCount, 0, 20);

        fileio::FileWriter::PromptToSave(stream, DEFAULT_FILENAME);

        fsm::Controller::Get().GoTo(fsm::States::MainMenu);
    }

}
