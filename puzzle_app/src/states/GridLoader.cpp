// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridLoader.cpp
// Date: 23/10/2019

#include "GridLoader.h"
#include "fileio/FileReader.h"
#include "fileio/FileWriter.h"
#include "fsm/Controller.h"

#include <peng/grid/Grid.h>
#include <Utils/Keyboard.h>
#include <Utils/Color.h>

#include <iostream>
#include <algorithm>
#include <sstream>

#define DEFAULT_GRID_SIZE 4
#define MENU_POSITIVE_OPTION 0

#define FILE_LOCATION "./15_files/random_puzzle.15f"
#define SAVE_FILE_LOCATION "./15_files/puzzle_solution.15f"


namespace screen {

    GridLoader::GridLoader() {

        const char* menuOptions[] = {
            "Yes",
            "No"
        };

        m_PrintToFileMenu = new WinTUI::Menu(menuOptions, 2);

        m_PrintToFileMenu->SetSelectedBefore([](std::ostream& ostream) {
            ostream << "* ";
            WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN);
            });
        m_PrintToFileMenu->SetSelectedAfter([](std::ostream& ostream) {
            WinTUI::Color::ResetConsoleColor();
            ostream << " *";
            });

        m_PrintToFileMenu->SetUnselectedBefore([](std::ostream& ostream) {
            ostream << "  ";
            });

        m_PrintToFileMenu->SetUnselectedAfter([](std::ostream& ostream) {
            ostream << "  ";
            });
    }

    GridLoader::~GridLoader() {
        delete m_PrintToFileMenu;
    }

    void GridLoader::OnEnter() {

        std::stringstream stream;

        ParseFile(FILE_LOCATION, stream);

        const char* question = "\nWould you like to save these solutions to a file?\n";
        m_PrintToFileMenu->SetFixtureBefore([=, &stream, &question](std::ostream& ostream) {
            ostream << stream.str();
            ostream << question;
            });
        m_PrintToFileMenu->Show(std::cout);

        if (m_PrintToFileMenu->GetLastSelected() == MENU_POSITIVE_OPTION) {
            bool success = fileio::FileWriter::WriteToFile(SAVE_FILE_LOCATION, stream);
            std::cout << std::endl;
            if (success) {
                std::cout << "Saved successfully to: \"" << SAVE_FILE_LOCATION << "\"" << std::endl;
            }
            else {
                std::cout << "Failed to save. Is \"" << SAVE_FILE_LOCATION << "\" open elsewhere?" << std::endl;
            }

            WinTUI::Keyboard::WaitForKey();
        }

        fsm::Controller::Get().GoTo(fsm::States::MainMenu);
    }

    bool GridLoader::EmptyString(std::string& str) {
        return str.empty() || (std::all_of(str.begin(), str.end(), isspace));
    }

    void GridLoader::ParseFile(const char* filePath, std::stringstream& stream) {
        fileio::FileReader file;

        bool readSuccess = file.ReadFile(filePath);
        if (!readSuccess) {
            std::cout << "Failed to read file: " << filePath << std::endl;
            WinTUI::Keyboard::WaitForKey();
            return;
        }

        fileio::FileLines fileLines = file.GetFileLines();

        unsigned int linePos = 0;

        std::string currentLine = fileLines.at(linePos++);

        const int gridCount = std::stoi(currentLine);

        stream << gridCount << std::endl;

        for (int currentGrid = 0; currentGrid < gridCount; ++currentGrid) {
            Peng::Grid<int> thisGrid;
            int tileArray[(DEFAULT_GRID_SIZE * DEFAULT_GRID_SIZE) - 1];
            int arrayStepper = 0;

            while (linePos < fileLines.size() && !EmptyString(currentLine = fileLines.at(linePos++))) {
                std::stringstream ss(currentLine);
                std::string token;

                while (ss >> token) {
                    tileArray[arrayStepper++] = std::stoi(token);
                }
            }
            thisGrid.SetTiles(tileArray, DEFAULT_GRID_SIZE);

            // TODO: pass this to grid solver and propagate through string stream
            stream << thisGrid;
            stream << std::endl;
        }
    }

}
