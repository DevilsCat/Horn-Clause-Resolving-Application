// Commands.h -- This file declares Command family for {Command Processor Pattern}.
// Created by Yu Xiao, Anqi Zhang, copyright preserved.
#ifndef COMMNADS_H
#define COMMANDS_H
#include "CommandProcessor.h"

// Interface for Command family, provides command type of derived class.
class Command {
public:
    // Declares all types of derived class.
    enum CommandType {
        kProcess = 0,
        kAssert,
        kUp,
        kDown,
        kResolve,
        kRandomize,
        kSet,
        kPrint,
        kUnknown
    };

    // First virtual method make this class polymophism.
    virtual ~Command();

    // All derived class should implement Excecute() method, so that each "command" can
    // let CommandProcessor execute associate function.
    virtual void Excecute(CommandProcessor& processor) = 0;
};

// Derived class of Command which let CommandProcessor execute "Process" command. 
class ProcessCommand : public Command {
public:
    // Takes a filename which contains well\bad-form horn clauses.
    explicit ProcessCommand(const std::string& filename);

    // Let CommandProcessor excecute "process" command.
    virtual void Excecute(CommandProcessor& processor) override;

private:
    // Stores the filename which contains well\bad-form horn clauses.
    std::string filename_;
};

// Derived class of Command which let CommandProcessor excute "Assert" command. 
class AssertCommand : public Command {
public:
    // Takes a string contains well\bad-form horn clauses.
    AssertCommand(const std::string& hornclauses);

    // Returns the string that contains well\bad-form horn clauses.
    std::string hornclauses() const;

    // Passes the string of horn clauses to CommandProcessor and let it excecute "assert" command
    virtual void Excecute(CommandProcessor& processor) override;
private:
    // Stores the string that contains horn clauses.
    std::string hornclauses_;
};

// Derived class of Command which let CommandProcessor excecute "resolve" command.
class ResolveCommand : public Command {
public:
    // Takes numbers of first and second horn clauses to resolve.
    ResolveCommand(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause);

    // Returns the number of first horn clause to resolve.
    unsigned num_first_hornclause() const;

    // Returns the number of second hor clause to resolve.
    unsigned num_second_hornclause() const;

    // Passes the numbers of horn clauses to CommandProcessor and let it excecute "resolve" command.
    virtual void Excecute(CommandProcessor& processor) override;

private:
    // Stores number of first horn clause in {DeductiveDatabase}.
    unsigned num_first_hornclause_;

    // Stores number of second horn clause in {DeductiveDatabase}.
    unsigned num_second_hornclause_;
};

// Derived class of Command which let CommandProcessor excecute "set" command.
class SetCommand : public Command {
public:
    // Takes variable to set and the value to set to.
    SetCommand(const std::string& variable, const unsigned& value);

    // Returns the variable to set new value.
    std::string variable() const;

    // Returns the value to set to.
    unsigned value() const;

    // Passes the variable and value to CommanProcessor and let it to excecute "set" command.
    virtual void Excecute(CommandProcessor& processor) override;
private:
    // Stores the variable to set new value.
    std::string variable_;

    // Sotres the value to set to.
    unsigned value_;
};

// Derived class of Command which let CommandProcessor excecute "randomize" command.
class RandomizeCommand : public Command {
public:
    // Takes the variable to randomize a new value to and maximum value for randomization upper bound.
    RandomizeCommand(const std::string& variable, const unsigned& max = 0);

    // Returns the variable to randomize a new value to.
    std::string variable() const;

    // Returns the maximum value for randomization upper bound.
    unsigned max() const;

    // Pass the variable and upperbound and let CommandProcessor to excecute "randomize" command.
    virtual void Excecute(CommandProcessor& processor) override;

private:
    // Stores the varaible to randomize a new value to.
    std::string variable_;
    
    // Stores the maximum value for randomization upper bound.
    unsigned max_;
};

// Derived class of Command which let CommandProcessor excecute "down" command.
class DownCommand : public Command {
public:
    // Takes numbers of line to scroll down.
    DownCommand(const unsigned& nlines = 0);
    
    // Returns the numbers of line to scroll down.
    unsigned nlines() const;

    // Pass numbers of lines to CommandProcessor and let it excecute "down" command.
    virtual void Excecute(CommandProcessor& processor) override;

private:
    // Stores the numbers of line to scroll down.
    unsigned nlines_;
};

// Derived class of Command which let CommandProcessor excecute "up" command.
class UpCommand : public Command {
public:
    // Takes numbers of line to scroll up.
    UpCommand(const unsigned& nlines = 0);

    // Returns the numbers of line to scroll up.
    unsigned nlines() const;

    // Pass numbers of line to CommandProcessor and let it excecute "up" command.
    virtual void Excecute(CommandProcessor& processor) override;

private:
    // Stores the numbers of line to scroll up.
    unsigned nlines_;
};

// Derived class of Command which let CommandProcessor execute "print" command.
class PrintCommand : public Command {
public:
    // Contrucotr.
    PrintCommand();

    // Let CommandProcessor to excectue "print" command.
    virtual void Excecute(CommandProcessor& processor) override;
};

#endif