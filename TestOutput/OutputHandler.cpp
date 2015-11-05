#include "stdafx.h"
#include "OutputHandler.h"
#include <windows.h>

OutputHandler::OutputHandler(std::ostream& os) :
    os_(os) 
{
    GetWindowSize();
}

void OutputHandler::CleanScreen() {
    system("cls");
}

int OutputHandler::GetWindowSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (ret) {
        width_ = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height_ = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return ret;
}