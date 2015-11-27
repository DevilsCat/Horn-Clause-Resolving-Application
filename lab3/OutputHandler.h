// OutputHandler.h -- This file declares a OutputHandler class to handle the console output.
// Created by Yu Xiao, Anqi Zhang. All right reserved.
//
#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H
#include <iostream>
#include <sstream>
#include <list>
#include <memory>

// Draws a UI and handle the console window size change. All the print in program
// should rerut to this class.
// Usage Sample:
//      auto OriginalPrint = []{ *OutputHandler::instance() << "hellow world" << std::endl; };
//      OutputHandler::instance()->DisplayProgram(OriginalPrint, "Title of Hello World");
//      // ... If error occurs
//      OutputHandler::instance()->LogError(error_string);
class OutputHandler {
    // Defines the header and footer of program.
    const std::string sTitleInfo =        "CSE 425 Lab 3: Resolving Horn Clause in C++";
    const std::string sCopyRight =        "By Anqi Zhang, Yu Xiao. ALL RIGHTS RESERVED";
    const std::string sDefaultTableName = "Default Table Name";
    const std::string sCommandWindow =    "Command Window";
    const std::string sPrompt =           ">>";
    const short nLinesTopUsed = 3;
    const short nLinesBottomUsed = 2 + 1;  // 1 for hint zone, 1 for empty usage.
public:
    // Returns singleton of this class.
    static std::shared_ptr<OutputHandler> instance();

    // Initialize singleton once.
    static void init(std::ostream&);

    // Returns the height of printable zone in run time.
    short GetPrintableZoneHeight() const;

    // Print hint only to the console screen.
    void DisplayHint(const std::string&) const;

    // Print prompt only to the console screen.
    void DisplayPrompt();

    // Logs the appeared error and display them later.
    void LogError(const std::string& e_what);

    // Reroute outside print std::endl to this class.
    OutputHandler& operator<<(std::ostream& (*F)(std::ostream&));
    
    // The program should use this to ouput the result, which will trigger the line logging.
    template<typename T>
    OutputHandler& operator<<(const T& v) {
        LogNumLinesUsed(v);
        out_ << v;
        return *this;
    }

    // Prints the whole program given user defined Functor.
    template<typename Func>
    void DisplayProgram(Func f, const std::string& table_name = std::string()) {
        system("cls");  // clear the screen.
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
    // For the sake of Singleton Pattern.
    OutputHandler(std::ostream& out);

    // Many utils function for drawing.
    static std::string center(const std::string& s, const int& w, const char delimiter);
    static std::string left(const std::string s, const int w, const char delimiter);
    static void gotoxy(const short& x, const short& y);
    static int GetWindowSize(short& width, short& height);
    static short GetWindowWidth();
    static short GetWindowHeight();
    static int GetCursorPos(short& x, short& y);
    void CursorBackToPrompt() const;

    // Display different sections of program.
    void DisplayHeader() const;
    void DisplayTableName(const std::string& = std::string()) const;
    void DisplaySeparatorBar(const std::string& name) const;
    void DisplayError();

    // Logs how many lines actually used by user.
    template<typename T>
    void LogNumLinesUsed(const T& v) {
        std::ostringstream oss(v);      // Use ostringstream to make sure all kind value can
        size_t len = oss.str().size();  // convert to string, so that we can know the length
        short window_width = GetWindowWidth();
        nline_user_used_ += short(ceil(double(len) / window_width));
    }

    // Stores the line used by user, before once {ProgramDisplay} called.
    static short nline_user_used_;

    // Stores the reference to a printable output.
    std::ostream& out_;

    // Stores the row of hint position.
    short hint_zone_row_;

    // Stores the current position of prompt.
    short prompt_x_, prompt_y_;

    // Stores the error occurs before once {PragramDisplay} called.
    std::list<std::string> error_list_;

    // Store the singleton of this class.
    static std::shared_ptr<OutputHandler> output_handler_;
};

#endif
