#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

int main() {
    auto data = readFile("../data/day2_input");
    
    int validCount = 0;
    int validCount2 = 0;
    for (auto const& line : data) {
        int idx = line.find("-");
        int from = std::stoi(line.substr(0, idx));
        int idx2 = line.find(" ");
        int to = std::stoi(line.substr(idx+1, idx2));
        char what = line[idx2+1];
        std::string password = line.substr(idx2+4);
        int count = std::count(password.begin(), password.end(), what);
        if (count >= from && count <= to) {
            validCount++;
        }
        if (password[from-1] == what ^ password[to-1] == what) {
            validCount2++;
        }
    }

    std::cout << validCount << std::endl;
    std::cout << validCount2 << std::endl;

    return 0;
}
