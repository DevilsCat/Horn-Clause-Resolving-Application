// Utils.h -- This file declares utility functions used in this program.
// Created by Yu Xiao, Anqi Zhang, all right reserved.
//
#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

#define DEFAULT_NUM_HORNCLAUSE  -1

// Returns true if given string is a non-negative number.
bool is_number(const std::string& s);

// Returns true if given string is all uppercase or all lowercase. 
bool is_variable(const std::string& s);

// Returns the unsigned value given a number string.
unsigned to_number(const std::string& num_str);

// Returns a vector of tokens given a line string.
std::vector<std::string> Tokenize(const std::string& line);

// Returns a encoded string padding with whitespace at the end.
std::string Encode(const std::string& str);

#endif