#include <iostream>
#include <string>
#include <vector>

#include "../library/io/files.h"

int main() {
    auto const data = readFile("../data/day1_input");
    int target = 2020;
    
    for (int idx1 = 0; idx1 < data.size(); idx1++) {
        int val1 = std::stoi(data[idx1]);
        for (int idx2 = idx1 + 1; idx2 < data.size(); idx2++) {
            int val2 = std::stoi(data[idx2]);
            if (val1 + val2 == target) {
                std::cout << "Two values: " << (val1 * val2) << std::endl;
            }
            for (int idx3 = idx2 + 1; idx3 < data.size(); idx3++) {
                int val3 = std::stoi(data[idx3]);
                if (val1 + val2 + val3 == target) {
                   std::cout << "Three values: " << (val1 * val2 * val3) << std::endl;
                }
            }
        }
    }
    
    return 0;
}
