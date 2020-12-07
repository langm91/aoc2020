#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

#include "../library/io/files.h"

int main() {
    auto data = readFile("../data/day6_input");

    long answer1 = 0;
    long answer2 = 0;

    std::set<char> anyAnswers {};
    std::set<char> allAnswers {};

    for (auto line : data) {
        if (line != "") {
            bool firstPerson = anyAnswers.empty();
            for (char a : line) {
                anyAnswers.insert(a);
                if (firstPerson) {
                    allAnswers.insert(a);
                }
            }
            if (!firstPerson) {
                for (auto a = allAnswers.begin(); a != allAnswers.end(); ) {
                    if (line.find(*a) == std::string::npos) {
                        a = allAnswers.erase(a);
                    } else {
                        ++a;
                    }
                }
            }
        } else {
            answer1 += anyAnswers.size();
            answer2 += allAnswers.size();
            anyAnswers.clear();
            allAnswers.clear();
        }
    }
    answer1 += anyAnswers.size();
    answer2 += allAnswers.size();

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
