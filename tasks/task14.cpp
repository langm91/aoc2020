#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include <bitset>

#include "../library/io/files.h"
#include "../library/text.h"

std::vector<long> modify(std::vector<long> source, long value, char mask) {
    std::vector<long> result {};
    for (auto v : source) {
        result.push_back(v | value);
        if (mask == 'X') result.push_back(v & ~value);
    }
    return result;
}

int main() {
    auto data = readFile("../data/day14_input");

    long answer1 = 0;
    long answer2 = 0;

    const int memlen = 34;
    std::string mask;
    std::map<long, long> memory {};
    std::map<long, long> memoryV2 {};

    for (auto line : data) {
        auto tokens = split(line, " ");
        if (tokens.at(0) == "mask") {
            mask = tokens.at(2);
        } else {
            long memloc = std::stol(line.substr(4, line.length()-6));
            std::vector<long> memlocsV2 { memloc };
            long memval = std::stol(tokens.at(2));
            long memvalV2 = memval;

            for (int idx = 0; idx < mask.length(); idx++) {
                char bit = mask.at(mask.length()-1-idx);
                long maskval = std::pow(2, idx);
                if (bit == '0') memval &= (~maskval);
                else memlocsV2 = modify(memlocsV2, maskval, bit);
                if (bit == '1') memval |= maskval;
            }

            memory[memloc] = memval;
            for (long ml2 : memlocsV2) {
                memoryV2[ml2] = memvalV2;
            }
        }
    }

    for (auto entry : memory) {
        answer1 += entry.second;
    }
    for (auto entry : memoryV2) {
        answer2 += entry.second;
    }

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
