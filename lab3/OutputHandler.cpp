#include "stdafx.h"
#include "OutputHandler.h"
#include <windows.h>

OutputHandler output_handler(std::cout);

short OutputHandler::nline_user_used_ = 0;

OutputHandler::OutputHandler(std::ostream& out) : 
    out_(out), hint_zone_row_(0), prompt_x_(0), prompt_y_(0)
{}

short OutputHandler::GetWindowWidth() const {
    short width = -1;
    short height = -1;
    GetWindowSize(width, height);
    return width;
}

short OutputHandler::GetWindowHeight() const {
    short width = -1;
    short height = -1;
    GetWindowSize(width, height);
    return height;
}

short OutputHandler::GetPrintableZoneHeight() const {
    short window_height = GetWindowHeight();
    return window_height < nLinesBottomUsed + nLinesTopUsed ? 0 : window_height - nLinesBottomUsed - nLinesTopUsed;
}

int OutputHandler::GetWindowSize(short& width, short& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (ret) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return ret;
}

int OutputHandler::GetCursorPos(short& x, short& y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (ret) {
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
    }
    return ret;
}

void OutputHandler::DisplayHeader() {
    out_ << center(sTitleInfo, GetWindowWidth(), ' ') << std::endl;
    out_ << center(sCopyRight, GetWindowWidth(), ' ') << std::endl;
}

void OutputHandler::DisplayTableName(const std::string& table_name) {
    const std::string to_display = table_name.empty() ? sDefaultTableName : table_name;
    out_ << center(to_display, GetWindowWidth(), '=') << std::endl;
}

void OutputHandler::DisplaySeparatorBar(const std::string& name) {
    out_ << left(name, GetWindowWidth(), '=') << std::endl;
}

void OutputHandler::DisplayError() {
    if (error_list_.empty()) return;
    *this << left("General Error", GetWindowWidth(), '=') << std::endl;
    for (const std::string e_what : error_list_) {
        *this << e_what << std::endl;
    }
}

void OutputHandler::DisplayHint(const std::string& hint) {
    short old_x, old_y;
    GetCursorPos(old_x, old_y);
    gotoxy(0, hint_zone_row_);
    std::cout << center(hint, GetWindowWidth(), ' ');
    gotoxy(old_x, old_y);
}

void OutputHandler::DisplayPrompt() {
    gotoxy(0, prompt_y_);
    out_ << left(sPrompt, GetWindowWidth(), ' ');
    CursorBackToPrompt();
}

void OutputHandler::LogError(const std::string& e_what) {
    error_list_.push_back(e_what);
}

void OutputHandler::CursorBackToPrompt() {
    gotoxy(prompt_x_, prompt_y_);
}

OutputHandler& OutputHandler::operator<<(std::ostream&(* F)(std::ostream&)) { 
    F(out_); 
    return *this; 
}

std::string OutputHandler::center(const std::string& s, const int& w, const char delimiter) {
    std::stringstream ss, spaces;
    int padding = w - s.size() - 1;                 // count excess room to pad
    for (int i = 0; i<padding / 2; ++i)
        spaces << delimiter;
    ss << spaces.str() << s << spaces.str();    // format with padding
    if (padding>0 && padding % 2 != 0)               // if odd #, add 1 space
        ss << delimiter;
    return ss.str();
}

/*! Left-aligns string within a field of width w. Pads with blank spaces
to enforce alignment. */
std::string OutputHandler::left(const std::string s, const int w, const char delimiter) {
    std::stringstream ss, spaces;
    int padding = w - s.size() - 1;                 // count excess room to pad
    for (int i = 0; i<padding; ++i)
        spaces << delimiter;
    ss << s << spaces.str();                    // format with padding
    return ss.str();
}


void OutputHandler::gotoxy(const short& x, const short& y) {
    COORD homeCoords = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), homeCoords);
}