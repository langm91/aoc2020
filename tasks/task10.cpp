#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "../library/io/files.h"

int fibonacci3(int a, int b, int c, int it) {
    if (it == 0) return c;
    else return fibonacci3(b, c, a+b+c, it-1);
}

int countPaths(int pathLength) {
    return fibonacci3(0, 0, 1, pathLength);
}

int main() {
    auto data = readLongFile("../data/day10_input");

    long answer1 = 0;
    long answer2 = 1;

    std::sort(data.begin(), data.end());

    long prev = 0;
    long ones = 0;
    std::map<int, int> diffs {
        std::pair<int, int>(1, 0),
        std::pair<int, int>(2, 0),
        std::pair<int, int>(3, 1)
    };
    for (long jolt : data) {
        int diff = jolt - prev;
        diffs.at(diff)++;
        prev = jolt;
        if (diff == 1) {
            ones++;
        } else if (diff == 3) {
            answer2 *= countPaths(ones);
            ones = 0;
        }
    }
    answer1 = diffs.at(1) * diffs.at(3);

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
