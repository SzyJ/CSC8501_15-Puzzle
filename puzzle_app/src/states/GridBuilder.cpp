// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridBuilder.cpp
// Date: 25/10/2019

#include "GridBuilder.h"
#include "fsm/Controller.h"
#include "fileio/FileWriter.h"

#include <Utils/Color.h>
#include <Utils/Keyboard.h>
#include <peng/grid/Grid.h>

#include <cctype>
#include <sstream>
#include <unordered_set>

#define GRID_SIZE 4
#define NUMBER_INPUT_MIN 0
#define NUMBER_INPUT_MAX 20

#define DEFAULT_FILENAME "custom_puzzle.15f"

#define GET_DIGITS(x) ((int) floor(log10(x)))


namespace screen {

    GridBuilder::GridBuilder() {
        ConfigureGridBuilder();
    }

    GridBuilder::~GridBuilder() {
        delete m_MatrixInput;
        delete m_GridBuilder;
    }

    void GridBuilder::ConfigureMatrixPrompt() {
        prompt = std::string("Enter a number between ");
        prompt.append(std::to_string(NUMBER_INPUT_MIN));
        prompt.append(" and ");
        prompt.append(std::to_string(NUMBER_INPUT_MAX));

        m_MatrixInput = new WinTUI::Prompt(prompt.c_str());

        m_MatrixInput->SetSelectedBefore([](std::ostream& ostream) {
            WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN);
        });
        m_MatrixInput->SetSelectedAfter([](std::ostream& ostream) {
            WinTUI::Color::ResetConsoleColor();
            ostream << ": ";
        });
        m_MatrixInput->SetCondition([](const char* string) {
            if (*string == '-') {
                return true;
            }

            char thisChar;
            for (int cIndex = 0; (thisChar = string[cIndex]) != '\0'; ++cIndex) {
                if (!std::isdigit(thisChar)) {
                    return false;
                }

                if (cIndex > GET_DIGITS(NUMBER_INPUT_MAX)) {
                    return false;
                }
            }

            return true;
        });
        m_MatrixInput->SetWarning([](std::ostream& ostream) {
            WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
            ostream << "Only enter " << (GET_DIGITS(NUMBER_INPUT_MAX) + 1) << " or less number characters" << std::endl;
        });
    }

    void GridBuilder::ConfigureGridBuilder() {
        m_GridBuilder = new WinTUI::Matrix<int>(GRID_SIZE, GRID_SIZE);

        m_GridBuilder->SetFixtureBefore([](std::ostream& ostream) {
            ostream << "1. Navigate to desired location with the arrow keys." << std::endl;
            ostream << "2. Press ENTER/SPACE to modify selected cell." << std::endl;
            ostream << "3. Enter the new desired value." << std::endl;
            ostream << "4. Once you are happy with the matrix, press ESC to exit." << std::endl;
            ostream << std::endl;
        });

        m_GridBuilder->SetSelectedBefore([](std::ostream& ostream) {
            WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN);
        });
        m_GridBuilder->SetSelectedAfter([](std::ostream& ostream) {
            WinTUI::Color::ResetConsoleColor();
        });

        m_GridBuilder->SetCStrConv([](const char* str, bool& success) {
            if (*str == '-') {
                success = true;
                return -1;
            }

            try {
                auto value = std::stoi(str);
                success = value >= NUMBER_INPUT_MIN && value <= NUMBER_INPUT_MAX;
                return value;
            } catch (const std::invalid_argument) {
                success = false;
                return -1;
            }
            catch (const std::out_of_range) {
                success = false;
                return -2;
            }
            catch (const std::exception) {
                success = false;
                return -3;
            }
        });

        m_GridBuilder->SetWarning([](std::ostream& ostream) {
            WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
            ostream << "Enter a positive number between " << NUMBER_INPUT_MIN << " and " << NUMBER_INPUT_MAX << std::endl;
        });

        ConfigureMatrixPrompt();

        m_GridBuilder->SetPrompt(m_MatrixInput);
    }


    bool GridBuilder::ValidateGridMatrix(int* array, int length, std::stringstream& info) {
        std::unordered_set<int> foundVals;
        for (int ind = 0; ind < (length - 1); ++ind) {
            int thisVal = array[ind];
            if (foundVals.find(thisVal) != foundVals.end()) {
                info << "Duplicate value found: " << thisVal;
                return false;
            }
            foundVals.insert(thisVal);
        }

        if (array[length - 1] >= 0) {
            info << "Bottom-Right value is not a empty space in this configuration";
            return false;
        }

        return true;
    }

    void GridBuilder::OnEnter() {
        std::stringstream infoStream;
        std::stringstream stream;
        bool validGrid = false;

        int* numArray;

        while (!validGrid) {
            m_GridBuilder->Show(std::cout);
            infoStream.str(std::string());
            if (ValidateGridMatrix((numArray = m_GridBuilder->GetMatrixArray()), GRID_SIZE * GRID_SIZE, infoStream)) {
                validGrid = true;
            } else {
                WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
                std::cout << infoStream.str();
                WinTUI::Color::ResetConsoleColor();
                std::cout << std::endl;

                WinTUI::Keyboard::WaitForKey();
            }
        }

        Peng::Grid<int> grid;
        grid.SetTiles(numArray, GRID_SIZE);
        stream << 1 << std::endl;
        stream << grid;

        fileio::FileWriter::PromptToSave(stream, DEFAULT_FILENAME);

        fsm::Controller::Get().GoTo(fsm::States::MainMenu);
    }


}
