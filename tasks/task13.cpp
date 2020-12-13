#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include "../library/io/files.h"
#include "../library/text.h"

using linfun = std::pair<long, long>;

/**
 * least-common-multiple with offset
 * lcmo(x, y, o, a0) -> a*x + o = b*y | a > a0
 */
long lcmo(long x, long y, long o, long& a0) {
    long result;
    while (((result = (++a0)*x) + o) % y != 0);
    return result;
}

linfun lcmof(long x, long y, long o) {
    long a0 = 0;
    long r1 = lcmo(x, y, o, a0);
    long r2 = lcmo(x, y, o, a0);
    return linfun(r1, r2-r1);
}

/**
 * least-common-multiple with linear functions
 * ggY(a1, b1, a2, b2, x0) -> a1+b1*x1 = a2+b2*x2 | x1 > x0
 */
long lcmlin(long a1, long b1, long a2, long b2, long& x0) {
    long result;
    while (((result = a1+b1*(++x0))-a2) % b2 != 0);
    return result;
}

linfun lcmlinf(long a1, long b1, long a2, long b2) {
    long a0 = 0;
    long r1 = lcmlin(a1, b1, a2, b2, a0);
    long r2 = lcmlin(a1, b1, a2, b2, a0);
    return linfun(r1, r2-r1);
}

int main() {
    auto data = readFile("../data/day13_input");

    long answer1 = 0;
    long answer2 = 0;

    long earliestPossibleTime = std::stol(data.at(0));
    long earliestBusDelay = earliestPossibleTime;
    int earliestBusId;
    strvec allBusLines = split(data.at(1), ",");
    std::vector<std::pair<int, int>> busLinesWithOffset {};
    int offset = 0;

    for (std::string busLine : allBusLines) {
        if (busLine != "x") {
            int busId = std::stoi(busLine);
            int nextBusDelay = busId - (earliestPossibleTime % busId);
            if (nextBusDelay < earliestBusDelay) {
                earliestBusDelay = nextBusDelay;
                earliestBusId = busId;
            }
            busLinesWithOffset.push_back(std::pair<int, int>(busId, offset));
        }
        offset++;
    }

    answer1 = earliestBusId * earliestBusDelay;

    const auto b0 = busLinesWithOffset.at(0);
    linfun curfun { 0, b0.first };
    for (auto b1 : busLinesWithOffset) {
        if (b1 != b0) {
            linfun b1fun = lcmof(b0.first, b1.first, b1.second);
            curfun = lcmlinf(curfun.first, curfun.second, b1fun.first, b1fun.second);
        }
    }

    answer2 = curfun.first;

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
