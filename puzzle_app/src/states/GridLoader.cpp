// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridLoader.cpp
// Date: 23/10/2019

#include "GridLoader.h"
#include "fileio/FileReader.h"
#include "fileio/FileWriter.h"
#include "fileio/Defaults.h"
#include "fsm/Controller.h"

#include <peng/grid/Grid.h>
#include <peng/grid/GridSolver.h>
#include <Utils/Keyboard.h>
#include <Utils/Color.h>

#include <iostream>
#include <algorithm>
#include <sstream>
#include <filesystem>

#define DEFAULT_GRID_SIZE 4
#define MENU_POSITIVE_OPTION 0

#define FILE_LOCATION "./15_files/random_puzzle.15f"
#define SAVE_FILENAME "puzzle_solution.15f"


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

    bool GridLoader::EmptyString(std::string& str) {
        return str.empty() || (std::all_of(str.begin(), str.end(), isspace));
    }

    void GridLoader::ParseFile(const char* filePath, std::stringstream& stream) const {
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

            unsigned long horizontalSeq;
            unsigned long verticalSeq;
            Peng::GridSolver::Do(thisGrid, 3, horizontalSeq, verticalSeq);
            stream << thisGrid;
            stream << "row = " << horizontalSeq << std::endl;
            stream << "column = " << verticalSeq << std::endl;
            stream << "reverse row = " << horizontalSeq << std::endl;
            stream << "reverse column = " << verticalSeq << std::endl;
            stream << std::endl;
        }
    }

    std::string GridLoader::GetUserChosenFile(const char* dirPath) {
        std::vector<std::string> allFiles;

        for (const auto& file : std::filesystem::directory_iterator(dirPath)) {
            if (file.is_regular_file()) {
                allFiles.push_back(file.path().filename().string());
            }
        }
        if (allFiles.empty()) {
            return std::string();
        }

        const char** fileChoices = new const char*[allFiles.size()];

        const int fileCount = allFiles.size();
        for (int fileInd = 0; fileInd < fileCount; ++fileInd) {
            fileChoices[fileInd] = allFiles.at(fileInd).c_str();
        }

        WinTUI::Menu fileSelector(fileChoices, fileCount);
        fileSelector.SetFixtureBefore([](std::ostream& ostream) {
            ostream << "Which file would you like to load?" << std::endl;
            });
        fileSelector.SetSelectedBefore([](std::ostream& ostream) {
            ostream << "* ";
            WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN);
            });
        fileSelector.SetSelectedAfter([](std::ostream& ostream) {
            WinTUI::Color::ResetConsoleColor();
            ostream << " *";
            });

        fileSelector.SetUnselectedBefore([](std::ostream& ostream) {
            ostream << "  ";
            });

        fileSelector.SetUnselectedAfter([](std::ostream& ostream) {
            ostream << "  ";
            });

        fileSelector.Show(std::cout);

        const int responseIndex = fileSelector.GetLastSelected();

        delete[] fileChoices;

        return allFiles.at(responseIndex);
    }

    void GridLoader::OnEnter() {

        std::stringstream stream;

        std::string fileName = GetUserChosenFile(FILE_DIRECTORY);
        if (fileName.empty()) {
            WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
            std::cout << "No valid files have been found!";
            WinTUI::Color::ResetConsoleColor();
            WinTUI::Keyboard::WaitForKey();

            fsm::Controller::Get().GoTo(fsm::States::MainMenu);
        }


        std::string filePath(FILE_DIRECTORY);
        filePath.append(fileName);

        ParseFile(filePath.c_str(), stream);

        fileio::FileWriter::PromptToSave(stream, SOLUTION_DIRECTORY, fileName.append(".solution").c_str());

        fsm::Controller::Get().GoTo(fsm::States::MainMenu);
    }

}
