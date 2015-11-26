#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H
#include "SymbolTable.h"
#include "DeductiveDatabase.h"
#include <mutex>

class CommandProcessor {
public:
    static std::shared_ptr<CommandProcessor> instance();
    static void init(const int&);
    
    virtual ~CommandProcessor();

    CommandProcessor(const CommandProcessor&) = delete;
    CommandProcessor& operator= (const CommandProcessor&) = delete;

    void Process(const std::string& filename);
    void Assert(const std::string& hornclauses);
    void Up(const unsigned& nlines = 0);
    void Down(const unsigned& nlines = 0);
    void Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause);
    void Randomize(std::string& variable, const unsigned& max = 0);
    void Set(std::string& variable, const int& value);
    void Print();

private:
    CommandProcessor(int);

    void DisplayDatabaseEntries(const unsigned& begin);
    short GetDefaultDisplayNum() const;

    SymbolTable symbol_table_;
    DeductiveDatabase database_;
    int display_counter_;
    int display_num_;

    static std::shared_ptr<CommandProcessor> cmd_processor_;
    static std::once_flag init_flag_;
};

#endif
