#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../library/io/files.h"
#include "../library/text.h"

int execute(std::vector<std::string> program, int& acc, int modifiedInstruction = 0) {
    std::vector<bool> visited (program.size(), false);
    int iteration = 1;
    int current = 0;
    acc = 0;

    while (true) {
        if (current >= visited.size()) {
            return 0;
        } else if (visited.at(current)) {
            return 1;
        }
        visited.at(current) = true;

        std::vector<std::string> instruction = split(program.at(current));
        std::string cmd = instruction.at(0);
        int param = std::stoi(instruction.at(1));

        if (iteration++ == modifiedInstruction) {
            if (cmd == "jmp") cmd = "nop";
            else if (cmd == "nop") cmd = "jmp";
        }

        if (cmd == "acc") {
            acc += param;
            current++;
        } else if (cmd == "jmp") {
            current += param;
        } else /*if (cmd == "nop")*/ {
            current++;
        }
    }
}

int main() {
    auto data = readFile("../data/day8_input");

    long answer1 = 0;
    long answer2 = 0;

    int acc = 0;
    int result = execute(data, acc);
    answer1 = acc;

    int modifiedInstruction = 1;
    while ((result = execute(data, acc, modifiedInstruction++)) > 0);
    answer2 = acc;

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
