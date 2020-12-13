#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../library/io/files.h"

int posMax(int val, int max) {
    val = val % max;
    if (val < 0) val += max;
    return val;
}

char getAction(int dir) {
    dir = posMax(dir, 360);
    return (dir == 0   ? 'E'
         : (dir == 90  ? 'N'
         : (dir == 180 ? 'W'
                       : 'S')));
}

void rotate (int &x, int &y, int degrees) {
    int range[] { x, -y, -x, y };
    int offset = degrees / 90;
    x = range[posMax(offset, 4)];
    y = range[posMax(3 + offset, 4)];
}

int main() {
    auto data = readFile("../data/day12_input");

    long answer1 = 0;
    long answer2 = 0;

    int x = 0, x2 = 0, wpOffX = 10;
    int y = 0, y2 = 0, wpOffY = 1;
    int dir = 0;
    for (auto instruction : data) {
        char action = instruction.at(0);
        int value = stoi(instruction.substr(1));

        if (action == 'N') wpOffY += value;
        if (action == 'S') wpOffY -= value;
        if (action == 'E') wpOffX += value;
        if (action == 'W') wpOffX -= value;
        if (action == 'L') rotate(wpOffX, wpOffY, value);
        if (action == 'R') rotate(wpOffX, wpOffY, -value);
        if (action == 'F') { x2 += (value * wpOffX); y2 += (value * wpOffY); };

        if (action == 'F') action = getAction(dir);
        if (action == 'N') y += value;
        if (action == 'S') y -= value;
        if (action == 'E') x += value;
        if (action == 'W') x -= value;
        if (action == 'L') dir += value;
        if (action == 'R') dir -= value;
    }

    answer1 = abs(x) + abs(y);
    answer2 = abs(x2) + abs(y2);

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
