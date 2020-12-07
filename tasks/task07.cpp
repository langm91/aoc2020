#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../library/io/files.h"

int main() {
    auto data = readFile("../data/day7_input");

    long answer1 = 0;
    long answer2 = 0;

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
