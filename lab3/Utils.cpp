#include "stdafx.h"
#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>
#include <windows.h>

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

bool is_variable(const std::string& s) {
    if (s.empty()) return false;
    return 
        std::find_if_not(s.begin(), s.end(), 
            [](char c) { return isupper(c); }) == s.end() ||
        std::find_if_not(s.begin(), s.end(), 
            [](char c) { return islower(c); }) == s.end();
}

unsigned to_number(const std::string& num_str) {
    return atoi(num_str.c_str());
}

std::vector<std::string> Tokenize(const std::string& line) {
    std::istringstream iss(line);
    return std::vector<std::string> {
        std::istream_iterator<std::string> {iss},
        std::istream_iterator<std::string> {}
    };
}

std::string Encode(const std::string& str) {
    return str + " ";
}

int Output::DisplayHeader(std::ostream& os) {
    const int line_use = 2;
    const std::string sTitleInfo = "CSE 425 Lab 3: Resolving Horn Clause in C++";
    const std::string sCopyRight = "Anqi Zhang, Yu Xiao. ALL RIGHTS RESERVED";
    std::cout << sTitleInfo << std::endl;
    std::cout << sCopyRight << std::endl;
    return line_use;
}

int Output::DisplayFooter(std::ostream& os) {
    const int line_use = 1;
    const std::string sPrompt = ">>";
    std::cout << sPrompt;
    return line_use;
}

int Output::GetWindowsSize(short& width, short& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (ret) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return ret;
}

void Output::DisplayProgram(std::ostream& os, void(* DisplayPredicate)(const int& max_nlines)) {
    short width, height;
    int ret = GetWindowsSize(width, height);
    if (!ret) { // Get Windows Size fail.
        return;
    } 
    int n_header = DisplayHeader(os);
    DisplayPredicate(height - n_header - 1);  // One line is for footer using.
    DisplayFooter(os);
}