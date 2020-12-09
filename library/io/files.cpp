#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "files.h"

strvec readFile(std::string fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        throw "Unable to read file " + fileName;
    }

    strvec lines;
    std::string line;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    return lines;
}