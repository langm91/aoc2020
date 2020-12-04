#include <string>
#include <vector>

#include "text.h"

std::vector<std::string> split(std::string text, std::string delimiter) {
    std::vector<std::string> result {};
    int start = 0;
    size_t idx = 0;
    while ((idx = text.find(delimiter, start)) != std::string::npos) {
        auto token = text.substr(start, idx-start);
        result.push_back(token);
        start = idx + 1;
    }
    auto token = text.substr(start);
    result.push_back(token);
    return result;
}