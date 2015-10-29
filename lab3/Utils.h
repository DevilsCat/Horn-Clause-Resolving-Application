#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

bool IsNumber(const std::string& s);

bool IsVariable(const std::string& s);

unsigned ToNumber(const std::string& num_str);

std::vector<std::string> Tokenize(const std::string& line);

#endif