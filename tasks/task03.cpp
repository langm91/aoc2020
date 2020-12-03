#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../library/io/files.h"

struct Slope {
    int slopeX;
    int slopeY;
};

std::ostream& operator<<(std::ostream& os, Slope const& arg) {
    os << "Slope " << arg.slopeX << "/" << arg.slopeY;
    return os;
}

int main() {
    auto data = readFile("../data/day3_input");
    
    const int patternWidth = data[0].length();
    Slope slopes[5] {
        Slope { 1, 1 },
        Slope { 3, 1 },
        Slope { 5, 1 },
        Slope { 7, 1 },
        Slope { 1, 2 }
    };

    long treeProduct = 1;
    for (Slope slope : slopes) {
        int treeCount = 0;
        int x = 0;
        for (int y = 0; y < data.size(); y += slope.slopeY) {
            if (data[y][x] == '#') {
                treeCount++;
            }
            x = (x + slope.slopeX) % patternWidth;
        }

        treeProduct *= treeCount;
        std::cout << slope << " - Trees: " << treeCount << std::endl;
    }

    std::cout << "Tree product: " << treeProduct << std::endl;

    return 0;
}
