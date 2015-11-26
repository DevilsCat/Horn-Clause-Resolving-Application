#ifndef COMMNADS_H
#define COMMANDS_H
#include "CommandProcessor.h"

class Command {
public:
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

    virtual ~Command();

    virtual void Excecute(CommandProcessor& processor) = 0;
};

class ProcessCommand : public Command {
public:
    explicit ProcessCommand(const std::string& filename);

    virtual void Excecute(CommandProcessor& processor) override;

private:
    std::string filename_;
};

class AssertCommand : public Command {
public:
    AssertCommand(const std::string& hornclauses);

    std::string hornclauses() const;

    virtual void Excecute(CommandProcessor& processor) override;
private:
    std::string hornclauses_;
};

class ResolveCommand : public Command {
public:
    ResolveCommand(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause);

    unsigned num_first_hornclause() const;
    unsigned num_second_hornclause() const;

    virtual void Excecute(CommandProcessor& processor) override;

private:
    unsigned num_first_hornclause_;
    unsigned num_second_hornclause_;
};

class SetCommand : public Command {
public:
    SetCommand(const std::string& variable, const unsigned& value);

    std::string variable() const;
    unsigned value() const;

    virtual void Excecute(CommandProcessor& processor) override;
private:
    std::string variable_;

    unsigned value_;
};

class RandomizeCommand : public Command {
public:
    RandomizeCommand(const std::string& variable, const unsigned& max = 0);

    std::string variable() const;
    unsigned max() const;

    virtual void Excecute(CommandProcessor& processor) override;

private:
    std::string variable_;

    unsigned max_;
};

class DownCommand : public Command {
public:
    DownCommand(const unsigned& nlines = 0);
    
    unsigned nlines() const;

    virtual void Excecute(CommandProcessor& processor) override;

private:
    unsigned nlines_;
};

class UpCommand : public Command {
public:
    UpCommand(const unsigned& nlines = 0);

    unsigned nlines() const;

    virtual void Excecute(CommandProcessor& processor) override;

private:
    unsigned nlines_;
};

class PrintCommand : public Command {
public:
    PrintCommand();

    virtual void Excecute(CommandProcessor& processor) override;
};

#endif