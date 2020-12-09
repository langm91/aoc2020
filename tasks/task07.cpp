#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <map>
#include <set>
#include <queue>

#include "../library/io/files.h"

int main() {
    auto data = readFile("../data/day7_input");

    long answer1 = 0;
    long answer2 = 0;

    const std::string myColor = "shiny gold bag";
    const std::regex bagRegex("[a-z]+ [a-z]+ bag");
    const std::regex bagCountRegex("[0-9]+ [a-z]+ [a-z]+ bag");
    std::map<std::string, std::set<std::string>> heldBy {};
    std::map<std::string, std::set<std::pair<std::string, int>>> holds {};

    for (auto line : data) {
        std::sregex_token_iterator bagsIt (line.begin(), line.end(), bagRegex);
        std::vector<std::string> bags { bagsIt, std::sregex_token_iterator() };
        std::sregex_token_iterator bagCountIt (line.begin(), line.end(), bagCountRegex);
        std::vector<std::string> bagCounts { bagCountIt, std::sregex_token_iterator() };

        std::string container = bags.front();
        for (auto bag : bags) {
            if (bag != container) {
                if (heldBy.find(bag) == heldBy.end()) {
                    heldBy.insert(std::pair<std::string, std::set<std::string>>(bag, {}));
                }
                heldBy.at(bag).insert(container);
            }
        }
        holds.insert(std::pair<std::string, std::set<std::pair<std::string, int>>>(container, {}));
        for (auto bag : bagCounts) {
            int count = std::stoi(bag.substr(0, bag.find(" ")));
            std::string color = bag.substr(bag.find(" ")+1);
            holds.at(container).insert(std::pair<std::string, int>(color, count));
        }
    }

    std::set<std::string> validBags {};
    std::queue<std::string> seed;
    seed.push(myColor);
    while (!seed.empty()) {
        std::string contained = seed.front();
        seed.pop();
        if (heldBy.find(contained) != heldBy.end()) {
            auto containers = heldBy.at(contained);
            for (auto c : containers) {
                if (validBags.find(c) == validBags.end()) {
                    validBags.insert(c);
                    seed.push(c);
                }
            }
        }
    }
    answer1 = validBags.size();

    std::queue<std::pair<std::string, int>> seed2;
    seed2.push(std::pair<std::string, int>(myColor, 1));
    answer2 -= 1; // The gold bag itself doesn't count

    while (!seed2.empty()) {
        std::pair<std::string, int> containerWithCount = seed2.front();
        seed2.pop();

        std::string container = containerWithCount.first;
        int count = containerWithCount.second;
        answer2 += count;

        if (holds.find(container) != holds.end()) {
            auto held = holds.at(container);
            for (auto h : held) {
                seed2.push(std::pair<std::string, int>(h.first, h.second*count));
            }
        }
    }

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
