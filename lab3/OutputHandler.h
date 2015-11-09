#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H
#include <iostream>
#include <sstream>
#include <list>

class OutputHandler {
    const std::string sTitleInfo = "CSE 425 Lab 3: Resolving Horn Clause in C++";
    const std::string sCopyRight = "By Anqi Zhang, Yu Xiao. ALL RIGHTS RESERVED";
    const std::string sDefaultTableName = "Default Table Name";
    const short nLinesTopUsed = 3;
    const std::string sCommandWindow = "Command Window";
    const std::string sPrompt = ">>";
    const short nLinesBottomUsed = 2 + 1;  // 1 for hint zone, 1 for empty usage.
public:
    static short nline_user_used_;

    OutputHandler(std::ostream& out);

    short GetPrintableZoneHeight() const;

    void DisplayHint(const std::string&);

    void DisplayPrompt();

    void LogError(const std::string& e_what);

    OutputHandler& operator<<(std::ostream& (*F)(std::ostream&));
    
    // The program should use this to ouput the result, which will trigger the line logging.
    template<typename T>
    OutputHandler& operator<<(const T& v) {
        LogNumLinesUsed(v);
        out_ << v;
        return *this;
    }

    template<typename Func>
    void DisplayProgram(Func f, const std::string& table_name = std::string()) {
        system("cls");
        DisplayHeader();
        DisplayTableName(table_name);
        
        // User printed predicate
        // Should always use operator<< in this class.
        f(GetPrintableZoneHeight());

        // User Error
        // Should list all the error occurs during operation
        DisplayError();

        if (nline_user_used_ < GetPrintableZoneHeight()) { // Some Line is not used, Move the cursor to the bottom.
            gotoxy(0, GetWindowHeight() - nLinesBottomUsed);
        }
        
        DisplaySeparatorBar(sCommandWindow);

        // Log the current cursor for HintZone.
        // Log the prompt cursor position.
        GetCursorPos(prompt_x_, prompt_y_);
        prompt_x_ += sPrompt.size();
        hint_zone_row_ = prompt_y_ + 1;

        nline_user_used_ = 0;  // Since the program display complete.
        error_list_.clear();
    }

private:
    static std::string center(const std::string& s, const int& w, const char delimiter);
    static std::string left(const std::string s, const int w, const char delimiter);
    static void gotoxy(const short& x, const short& y);
    static int GetWindowSize(short& width, short& height);
    short GetWindowWidth() const;
    short GetWindowHeight() const;
    static int GetCursorPos(short& x, short& y);
    void CursorBackToPrompt();

    void DisplayHeader();
    void DisplayTableName(const std::string& = std::string());
    void DisplaySeparatorBar(const std::string& name);
    void DisplayError();

    template<typename T>
    void LogNumLinesUsed(const T& v) {
        std::ostringstream oss(v);      // Use ostringstream to make sure all kind value can
        size_t len = oss.str().size();  // convert to string, so that we can know the length
        short window_width = GetWindowWidth();
        nline_user_used_ += short(ceil(double(len) / window_width));
    }

    std::ostream& out_;

    short hint_zone_row_;

    short prompt_x_, prompt_y_;

    std::list<std::string> error_list_;
};

#endif
