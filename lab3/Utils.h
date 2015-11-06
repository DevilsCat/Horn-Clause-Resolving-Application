#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include "OutputHandler.h"

extern OutputHandler output_handler;

#define DEFAULT_NUM_HORNCLAUSE  -1

bool is_number(const std::string& s);

bool is_variable(const std::string& s);

unsigned to_number(const std::string& num_str);

std::vector<std::string> Tokenize(const std::string& line);

std::string Encode(const std::string& str);

//namespace Output {
//    const std::string sTitleInfo = "CSE 425 Lab 3: Resolving Horn Clause in C++";
//    const std::string sCopyRight = "By Anqi Zhang, Yu Xiao. ALL RIGHTS RESERVED";
//    const short iNumLineUsed = 2;
//
//    int DisplayHeader(std::ostream& os, const short& width);
//    int GetWindowSize(short& width, short& height);
//    short GetPrintableZoneHeight();
//    std::string center(const std::string s, const int w);
//    void gotoxy(const short& x, const short& y);
//
//    template<typename Func>
//    void DisplayProgram(std::ostream& os, Func f) {
//        system("cls");
//        short width, height;
//        int ret = GetWindowSize(width, height);
//        if (!ret) { // Get Windows Size fail.
//            return;
//        }
//        int n_header = DisplayHeader(os, width);
//        
//        short n_usage = f(height - n_header - 1);  // One line is for next prompt
//        
//        if (n_usage < height - n_header - 1) { // Some Line is not used, Move the cursor to the bottom.
//            gotoxy(0, height - 1);
//        }
//    }
//
//}

#endif