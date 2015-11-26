// CommandProcessor.h -- This file declares CommandProcessor class {CommandProcessor Pattern}.
// Created by Yu Xiao, Anqi Zhang, Copyright preserved.
//
#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H
#include "SymbolTable.h"
#include "DeductiveDatabase.h"
#include <mutex>

//
// class CommandProcessor
// This class passively processes command that calls it. It contains all commands
// that works on horn clauses.
// It applies singleton pattern so that program has only exactly one singleton.
// It is used in Command Processor pattern so that "Commands" can be executed on
// CommandProcessor singleton.
// Example:
//  CommandProcessor::init(num);
//  ... Make a {Command} family object command.
//  command->Exececute(*CommandProcessor::instance());
//
class CommandProcessor {
public:
    //
    // instance()
    // returns the singleton of CommandProcess class. Throws ProgramExecption
    // with type FatalError if init() was not called before this call.
    //
    static std::shared_ptr<CommandProcessor> instance();
    
    //
    // init()
    // Allocates and initializes the CommandProcessor singleton with given
    // integer for default numbers hornclauses.
    //
    static void init(const int&);

    //
    // deleted functions
    // Makes this class uncopiable.
    //
    CommandProcessor(const CommandProcessor&) = delete;
    CommandProcessor& operator= (const CommandProcessor&) = delete;
    
    // "Do-work" horn clause command function family.
    //
    // Process()
    // loads and parses a file of Horn clauses, adds well formed Horn clauses 
    // from that file to the symbol table, and re-displays the numbered list 
    // of Horn clauses, starting from the top of the list.
    //
    void Process(const std::string& filename);
    //
    // Assert()
    // parses the rest of the line following the assert keyword to identify 
    // one or more well formed Horn clauses, adds the bound variables, numeric 
    // constants, and predicates of any of them that are well formed to the 
    // symbol table, and re-displays the numbered list of Horn clauses, 
    // starting from the top of the list.
    //
    void Assert(const std::string& hornclauses);
    //
    // Up()
    // scrolls up a full screen if no number is given following the command, or 
    // scrolls up the number of lines given if a number was given (scrolling 
    // should stop at the top of the list if it is reached).
    //
    void Up(const unsigned& nlines = 0);
    //
    // Down()
    // scrolls down a full screen if no number is given following the command, 
    // or scrolls down the number of lines given if a number was given (scrolling 
    // should stop at the bottom of the list if it is reached).
    //
    void Down(const unsigned& nlines = 0);
    //
    // Resolve()
    // resolves the Horn clauses whose numbers (in the list) are given in the command.
    //
    void Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause);
    //
    // Randomize()
    // generates a randomized value for a bound variable.
    void Randomize(std::string& variable, const unsigned& max = 0);
    //
    // Set()
    // sets a bound variable to the given value.
    //
    void Set(std::string& variable, const int& value);
    //
    // Print()
    // prints out the contents of the symbol table including both predicates and bound 
    // variables (with their values, for the latter).
    //
    void Print();

private:
    //
    // Constructor
    // Initializes CommandProcessor object, since Singleton Pattern, this should be
    // only call once by ::init().
    //
    CommandProcessor(int);

    //
    // DisplayDatatbaseEntries_()
    // Displays the database entries given the begin position.
    //
    void DisplayDatabaseEntries_(const unsigned& begin);

    //
    // GetMaxDisplayNum()
    // Returns passed in numbers of horn clause when this object is constructed, if
    // that number is not DEFAULT_NUM_HORNCLAUSE, otherwise, return the printible
    // zone height as display number.
    //
    short GetMaxDisplayNum() const;

    // Stores all boudned varialbes and predicates that recognized by processor.
    SymbolTable symbol_table_;
    // Stores all processed and resolved hornclauses.
    DeductiveDatabase database_;
    // Stores the current display start point.
    int display_counter_;
    // Stores the numbers of line to display the horn clauses.
    int display_num_;

    // Used in Singleton Pattern.
    static std::shared_ptr<CommandProcessor> cmd_processor_;
    // Ensures init() will has only one time effect.
    static std::once_flag init_flag_;
};

#endif
