#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../library/io/files.h"

int width;
int height;
const char occupied = '#';
const char empty = 'L';
const char nothing = '.';

char calcNewState(int midX, int midY, strvec world) {
    int occupiedNeighbors = 0;
    for (int x = midX - 1; x <= midX + 1; x++) {
        for (int y = midY - 1; y <= midY + 1; y++) {
            if (x >= 0 && x < width && y >= 0 && y < height
                    && (midX != x || midY != y)
                    && world.at(y).at(x) == occupied) {
                occupiedNeighbors++;
            }
        }
    }
    if (world.at(midY).at(midX) == empty && occupiedNeighbors == 0) {
        return occupied;
    } else if (world.at(midY).at(midX) == occupied && occupiedNeighbors >= 4) {
        return empty;
    } else {
        return world.at(midY).at(midX);
    }
}

char firstVisible(strvec world, int midX, int midY, int(*xFun)(int), int(*yFun)(int)) {
    int x = midX, y = midY;
    while (true) {
        x = xFun(x);
        y = yFun(y);
        if (x >= 0 && x < width && y >= 0 && y < height) {
            if (world.at(y).at(x) != nothing) {
                return world.at(y).at(x);
            }
        } else {
            break;
        }
    }
    return nothing;
}

int pos(int v) { return v+1; }
int neg(int v) { return v-1; }
int id(int v) { return v; }

char calcNewState2(int midX, int midY, strvec world) {
    int occupiedNeighbors = 0;
    int(*dirs[3])(int) { &pos, &neg, &id };
    for (auto xDir : dirs) {
        for (auto yDir : dirs) {
            if ((xDir != id || yDir != id) && firstVisible(world, midX, midY, xDir, yDir) == occupied) {
                occupiedNeighbors++;
            }
        }
    }
    if (world.at(midY).at(midX) == empty && occupiedNeighbors == 0) {
        return occupied;
    } else if (world.at(midY).at(midX) == occupied && occupiedNeighbors >= 5) {
        return empty;
    } else {
        return world.at(midY).at(midX);
    }
}

int permutate(strvec oldWorld, strvec* newWorld, char(*calcFunction)(int, int, strvec)) {
    int changeCount = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char newState = calcFunction(x, y, oldWorld);
            if (newWorld->at(y).at(x) != newState) {
                newWorld->at(y).at(x) = newState;
                changeCount++;
            }
        }
    }

    return changeCount;
}

int main() {
    auto data = readFile("../data/day11_input");

    long answer1 = 0;
    long answer2 = 0;

    width = data.at(0).size();
    height = data.size();

    strvec oldWorld (data);
    strvec newWorld (data);
    while (permutate(oldWorld, &newWorld, &calcNewState) > 0) {
        strvec temp = oldWorld;
        oldWorld = newWorld;
        newWorld = temp;
    }

    strvec oldWorld2 (data);
    strvec newWorld2 (data);
    while (permutate(oldWorld2, &newWorld2, &calcNewState2) > 0) {
        strvec temp = oldWorld2;
        oldWorld2 = newWorld2;
        newWorld2 = temp;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (newWorld.at(y).at(x) == occupied) {
                answer1++;
            }
            if (newWorld2.at(y).at(x) == occupied) {
                answer2++;
            }
        }
    }
    

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;

    return 0;
}
