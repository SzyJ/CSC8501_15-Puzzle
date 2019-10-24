// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridLoader.cpp
// Date: 24/10/2019

#include "GridLoader.h"
#include "fileio/FileReader.h"
#include "fileio/FileWriter.h"
#include "fileio/Defaults.h"
#include "fsm/Controller.h"

#include <peng/grid/GridSolver.h>
#include <Utils/Keyboard.h>
#include <Utils/Color.h>

#include <iostream>
#include <algorithm>
#include <sstream>
#include <filesystem>
#include <thread>

#define EXPECTED_GRID_SIZE 4

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

        const bool readSuccess = file.ReadFile(filePath);
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

        std::vector<std::stringstream*> streams;
        std::vector<std::thread*> threadPool;
        for (int currentGrid = 0; currentGrid < gridCount; ++currentGrid) {
            auto* thisGrid = new Peng::Grid<int>();

            //int tileArray[(DEFAULT_GRID_SIZE * DEFAULT_GRID_SIZE) - 1];
            std::vector<int> tileArray;
            tileArray.reserve((EXPECTED_GRID_SIZE * EXPECTED_GRID_SIZE) - 1);

            bool widthFound = false;
            unsigned int heightCounter = 0;
            unsigned int widthCounter = 0;

            while (linePos < fileLines.size() && !EmptyString(currentLine = fileLines.at(linePos++))) {
                std::stringstream ss(currentLine);
                std::string token;

                ++heightCounter;
                while (ss >> token) {
                    if (!widthFound) {
                        ++widthCounter;
                    }
                    tileArray.push_back(std::stoi(token));
                }
                widthFound = true;
            }
            thisGrid->SetTiles(tileArray.data(), widthCounter, heightCounter);

            streams.emplace_back(new std::stringstream);
            std::stringstream* thisStream = streams.back();

            std::thread* thisThread = new std::thread([=] { PrintGridSolutions(thisGrid, *thisStream); });
            threadPool.push_back(thisThread);
        }

        for (std::thread* t : threadPool) {
            t->join();
            delete t;
        }

        for (std::stringstream* ss : streams) {
            stream << ss->str();
            delete ss;
            stream << std::endl;
        }
    }

    void GridLoader::PrintGridSolutions(Peng::Grid<int>* grid, std::stringstream& stream) {
        unsigned long long horizontalSeq;
        unsigned long long verticalSeq;
        const unsigned int defaultLength = grid->GetWidth();

        Peng::GridSolver::CountAll(*grid, defaultLength, horizontalSeq, verticalSeq);
        stream << *grid;
        stream << "row = " << horizontalSeq << std::endl;
        stream << "column = " << verticalSeq << std::endl;
        stream << "reverse row = " << horizontalSeq << std::endl;
        stream << "reverse column = " << verticalSeq << std::endl;
        stream << "(total for row and column, including reverse, in this configuration)" << std::endl;
        unsigned long thisConfigTotal;
        for (int seqLen = 2; seqLen <= defaultLength; ++seqLen) {
            Peng::GridSolver::CountThis(*grid, seqLen, thisConfigTotal);
            stream << seqLen << " = " << thisConfigTotal << std::endl;
        }
        stream << "(total for row and column, including reverse, for all valid turns)" << std::endl;
        for (int seqLen = 2; seqLen <= defaultLength; ++seqLen) {
            Peng::GridSolver::CountAll(*grid, seqLen, horizontalSeq, verticalSeq);
            stream << seqLen << " = " << ((horizontalSeq + verticalSeq) * 2) << std::endl;
        }

        delete grid;
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
