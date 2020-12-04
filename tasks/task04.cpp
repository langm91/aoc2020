#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

#include "../library/io/files.h"
#include "../library/text.h"
#include "../library/math.h"

class Validator {
    public:
        Validator(std::function<bool(std::string)> fun) {
            this->_fun = fun;
        }

        bool validate(std::string input) {
            return _fun(input);
        }
    private:
        std::function<bool(std::string)> _fun;
};

std::pair<std::string, Validator*> createValidatorEntry(std::string key, std::function<bool(std::string)> fun) {
    return std::pair<std::string, Validator*> (key, new Validator(fun));
}

const std::map<std::string, Validator*> validators {
    createValidatorEntry("byr", ([](std::string v) { return between(v, 1920, 2002); })),
    createValidatorEntry("iyr", ([](std::string v) { return between(v, 2010, 2020); })),
    createValidatorEntry("eyr", ([](std::string v) { return between(v, 2020, 2030); })),
    createValidatorEntry("hgt", ([](std::string v) {
        std::string unit = v.substr(v.size()-2);
        std::string hgt = v.substr(0, v.size()-2);
        if (unit == "cm") return between(hgt, 150, 193);
        if (unit == "in") return between(hgt, 59, 76);
        return false;
    })),
    createValidatorEntry("hcl", ([](std::string v) { return std::regex_match(v, std::regex("#[0-9a-f]{6}")); })),
    createValidatorEntry("ecl", ([](std::string v) {
        std::vector<std::string> valid { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
        return std::find(valid.begin(), valid.end(), v) != valid.end();
    })),
    createValidatorEntry("pid", ([](std::string v) { return std::regex_match(v, std::regex("[0-9]{9}")); })),
    createValidatorEntry("cid", ([](std::string v) { return true; })),
};

bool validate(std::map<std::string, std::string> passport) {
    for (auto const& [key, val] : passport) {
        if (!validators.at(key)->validate(val)) {
            return false;
        }
    }
    return true;
}

int main() {
    auto data = readFile("../data/day4_input");

    long answer1 = 0;
    long answer2 = 0;

    const int requiredFieldCount = 8;
    std::map<std::string, std::string> passport { {"cid", ""} };

    for (auto line : data) {
        if (line == "") {
            if (passport.size() >= requiredFieldCount) {
                answer1++;
                if (validate(passport)) {
                    answer2++;
                }
            }
            passport = { {"cid", ""} };
        } else {
            std::vector<std::string> tokens = split(line, " ");
            for (auto token : tokens) {
                std::vector<std::string> kv = split(token, ":");
                passport.insert(std::pair<std::string, std::string>(kv[0], kv[1]));
            }
        }
    }

    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;
    return 0;
}
