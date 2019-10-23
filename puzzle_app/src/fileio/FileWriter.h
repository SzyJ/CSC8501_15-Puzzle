// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: FileWriter.h
// Date: 21/10/2019

#pragma once

#include <sstream>
#include <fstream>
#include <string>

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

    };

}
