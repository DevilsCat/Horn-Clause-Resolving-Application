#pragma once
#include <iostream>

class OutputHandler {
    const char* sTitle = "CSE 425 Lab 3: Resolving Horn Clause in C++";
    const char* sCopyRight = "By Anqi Zhang, Yu Xiao. ALL RIGHTS RESERVED";
public:
    OutputHandler(std::ostream& os);

    void CleanScreen();

    int GetWindowSize();

private:
    std::ostream& os_;
    short width_, height_;
};
