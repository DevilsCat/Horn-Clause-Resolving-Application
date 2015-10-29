#include "stdafx.h"
#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>

bool IsNumber(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

unsigned ToNumber(const std::string& num_str) {
    return atoi(num_str.c_str());
}

std::vector<std::string> Tokenize(const std::string& line) {
    std::istringstream iss(line);
    return std::vector<std::string> {
        std::istream_iterator<std::string> {iss},
        std::istream_iterator<std::string> {}
    };
}