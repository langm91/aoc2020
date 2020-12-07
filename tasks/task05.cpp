#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

#include "../library/io/files.h"

int main() {
    auto data = readFile("../data/day5_input");

    long answer1 = 0;
    long answer2 = 0;

    std::set<long> seats {};

    for (std::string bsp : data) {
        std::replace(bsp.begin(), bsp.end(), 'F', '0');
        std::replace(bsp.begin(), bsp.end(), 'B', '1');
        std::replace(bsp.begin(), bsp.end(), 'L', '0');
        std::replace(bsp.begin(), bsp.end(), 'R', '1');
        int row = std::stoi(bsp.substr(0, 7), 0, 2);
        int column = std::stoi(bsp.substr(7, 10), 0, 2);
        long seatId = row*8 + column;
        seats.insert(seatId);

        answer1 = std::max(answer1, seatId);
    }

    long prevSeat = 0;
    for (long seat : seats) {
        if (prevSeat > 0 && prevSeat + 1 != seat) {
            answer2 = seat - 1;
            break;
        }
        prevSeat = seat;
    }

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
