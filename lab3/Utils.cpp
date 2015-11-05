#include "stdafx.h"
#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <functional>

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

int Output::DisplayHeader(std::ostream& os, const short& width) {
    const int line_use = 2;
    std::cout << center(sTitleInfo, width - 1) << std::endl;
    std::cout << center(sCopyRight, width - 1) << std::endl;
    return line_use;
}

int Output::GetWindowSize(short& width, short& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (ret) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return ret;
}

short Output::GetPrintableZoneHeight() {
    short width, height;
    GetWindowSize(width, height);
    return height < iNumLineUsed ? 0 : height - iNumLineUsed;
}

std::string Output::center(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int padding = w - s.size();                 // count excess room to pad
    for (int i = 0; i<padding / 2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();    // format with padding
    if (padding>0 && padding % 2 != 0)               // if odd #, add 1 space
        ss << " ";
    return ss.str();
}

void Output::gotoxy(const short& x, const short& y) {
    COORD homeCoords = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCoords);
}