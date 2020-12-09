#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../library/io/files.h"

bool validate (std::vector<long> data, int from, int to, long sum) {
    for (int idx = from; idx < to; idx++) {
        long v1 = data.at(idx);
        if (v1 < sum) {
            for (int idx2 = idx + 1; idx2 < to; idx2++) {
                long v2 = data.at(idx2);
                if (v1 + v2 == sum) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    auto data = readFile("../data/day9_input");

    long answer1 = 0;
    long answer2 = 0;

    const int preamble = 25;
    std::vector<long> xmas {};
    for (auto line : data) xmas.push_back(std::stol(line));

    int idx = 0;
    while (validate(xmas, idx, idx + preamble + 1, xmas.at(idx + preamble + 1))) {
        idx++;
    }
    answer1 = xmas.at(idx + preamble + 1);

    for (int start = 0; start < xmas.size() && answer2 == 0; start++) {
        int sum = 0;
        long min = xmas.at(start);
        long max = xmas.at(start);
        for (int idx = start; idx < xmas.size(); idx++) {
            int num = xmas.at(idx);
            sum += num;
            if (sum > answer1) {
                break;
            }
            if (num > max) max = num;
            if (num < min) min = num;
            if (sum == answer1) {
                answer2 = min + max;
                break;
            }
        }
    }

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
