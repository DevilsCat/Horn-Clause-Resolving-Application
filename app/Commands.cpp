// Commands.cpp -- This file defines Command family for {Command Processor Pattern}.
// Created by Yu Xiao, Anqi Zhang, all right reserved.
#include "stdafx.h"
#include "Commands.h"

Command::~Command() {}

// Class ProcessCommand Implementation.
void ProcessCommand::Excecute(CommandProcessor& processor) {
    processor.Process(filename_);
}

ProcessCommand::ProcessCommand(const std::string& filename) :
filename_(filename)
{}

// Class AssertCommand Implementation.
AssertCommand::AssertCommand(const std::string& hornclauses) :
hornclauses_(hornclauses)
{}

std::string AssertCommand::hornclauses() const {
    return hornclauses_;
}

void AssertCommand::Excecute(CommandProcessor& processor) {
    processor.Assert(hornclauses_);
}

// Class ResolveCommand Implementation.
ResolveCommand::ResolveCommand(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause) :
num_first_hornclause_(num_first_hornclause), num_second_hornclause_(num_second_hornclause)
{}

unsigned ResolveCommand::num_first_hornclause() const {
    return num_first_hornclause_;
}

unsigned ResolveCommand::num_second_hornclause() const {
    return num_second_hornclause_;
}

void ResolveCommand::Excecute(CommandProcessor& processor) {
    processor.Resolve(num_first_hornclause_, num_second_hornclause_);
}

// Class SetCommand Implementation.
SetCommand::SetCommand(const std::string& variable, const unsigned& value) :
variable_(variable), value_(value)
{}

std::string SetCommand::variable() const {
    return variable_;
}

unsigned SetCommand::value() const {
    return value_;
}

void SetCommand::Excecute(CommandProcessor& processor) {
    processor.Set(variable_, value_);
}

// Class RandomizeCommand Implementation.
RandomizeCommand::RandomizeCommand(const std::string& variable, const unsigned& max) :
variable_(variable), max_(max)
{}

std::string RandomizeCommand::variable() const {
    return variable_;
}

unsigned RandomizeCommand::max() const {
    return max_;
}

void RandomizeCommand::Excecute(CommandProcessor& processor) {
    processor.Randomize(variable_, max_);
}

// Class DownCommand Implementation.
DownCommand::DownCommand(const unsigned& nlines) :
nlines_(nlines)
{}

unsigned DownCommand::nlines() const {
    return nlines_;
}

void DownCommand::Excecute(CommandProcessor& processor) {
    processor.Down(nlines_);
}

// Class UpCommand Implementation.
UpCommand::UpCommand(const unsigned& nlines) :
nlines_(nlines)
{}

unsigned UpCommand::nlines() const {
    return nlines_;
}

void UpCommand::Excecute(CommandProcessor& processor) {
    processor.Up(nlines_);
}

// Class PrintCommand Implementation.
PrintCommand::PrintCommand() {}

void PrintCommand::Excecute(CommandProcessor& processor) {
    processor.Print();
}