// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: FileWriter.h
// Date: 21/10/2019

#pragma once
#include "fileio/Defaults.h"

#include <Utils/Color.h>
#include <Utils/Keyboard.h>

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#define MENU_POSITIVE_OPTION 0

namespace fileio {

    class FileWriter {
    public:
        static bool WriteToFile(const char* filepath, std::stringstream& payload) {
            std::ofstream file(filepath);
            if (!file.is_open()) {
                return false;
            }

            file << payload.str();
            file.close();

            return true;
        }

        static inline void PromptToSave(std::stringstream& toPrint, const char* fileName) {
            PromptToSave(toPrint, FILE_DIRECTORY, fileName);
        }

        static inline void PromptToSave(std::stringstream& toPrint, const char* dirPath, const char* fileName) {
            const char* menuOptions[] = {
            "Yes",
            "No"
            };

            WinTUI::Menu printToFileMenu(menuOptions, 2);

            printToFileMenu.SetSelectedBefore([](std::ostream& ostream) {
                ostream << "* ";
                WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN);
                });
            printToFileMenu.SetSelectedAfter([](std::ostream& ostream) {
                WinTUI::Color::ResetConsoleColor();
                ostream << " *";
                });

            printToFileMenu.SetUnselectedBefore([](std::ostream& ostream) {
                ostream << "  ";
                });

            printToFileMenu.SetUnselectedAfter([](std::ostream& ostream) {
                ostream << "  ";
                });

            const char* question = "\nWould you like to save this to a file?\n";

            printToFileMenu.SetFixtureBefore([=, &toPrint, &question](std::ostream& ostream) {
                ostream << toPrint.str();
                ostream << question;
                });

            printToFileMenu.Show(std::cout);

            if (printToFileMenu.GetLastSelected() == MENU_POSITIVE_OPTION) {
                std::string filePath(dirPath);
                filePath.append(fileName);

                bool success = fileio::FileWriter::WriteToFile(filePath.c_str() , toPrint);
                std::cout << std::endl;
                if (success) {
                    std::cout << "Saved successfully to: \"" << filePath << "\"" << std::endl;
                } else {
                    std::cout << "Failed to save. Is \"" << filePath << "\" open elsewhere?" << std::endl;
                }

                WinTUI::Keyboard::WaitForKey();
            }
        }

    };

}
