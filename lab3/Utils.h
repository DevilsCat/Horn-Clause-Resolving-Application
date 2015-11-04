#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

#define DEFAULT_NUM_HORNCLAUSE  10

bool is_number(const std::string& s);

bool is_variable(const std::string& s);

unsigned to_number(const std::string& num_str);

std::vector<std::string> Tokenize(const std::string& line);

std::string Encode(const std::string& str);

namespace Output {
    int DisplayHeader(std::ostream& os);
    int DisplayFooter(std::ostream& os);
    int GetWindowsSize(short& width, short& height);

    void DisplayProgram(std::ostream& os, void (*DisplayPredicate)(const int& max_nlines));


}

#endif