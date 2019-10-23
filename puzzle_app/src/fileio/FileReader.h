// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: FileReader.h
// Date: 23/10/2019

#pragma once
#include <fstream>
#include <vector>
#include <string>

namespace fileio {

    typedef std::vector<std::string> FileLines;

    class FileReader {
    public:
        FileReader() = delete;

        bool ReadFile(const char* filepath) {
            std::ifstream file(filepath);
            std::string line;
            if (!file.is_open()) {
                return false;
            }

            while (std::getline(file, line)) {
                fileLines.emplace_back(line);
            }

            file.close();
        }

        FileLines GetFileLines() { return fileLines; }

    private:
        FileLines fileLines;

    };

}
