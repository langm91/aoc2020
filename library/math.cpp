#include <string>

#include "math.h"

bool between (std::string value, int min, int max) {
    int v = std::stoi(value);
    return v >= min && v <= max;
};