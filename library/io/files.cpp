#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "files.h"

std::vector<std::string> readFile(std::string fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        throw "Unable to read file " + fileName;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    return lines;
}