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

std::vector<long> readLongFile(std::string fileName) {
    strvec file = readFile(fileName);
    std::vector<long> longFile {};
    for (auto line : file) longFile.push_back(std::stol(line));
    return longFile;
}