#include "stdafx.h"
#include "AssertCommand.h"

AssertCommand::AssertCommand(const std::string& hornclauses) :
    hornclauses_(hornclauses)
{}

std::string AssertCommand::hornclauses() {
    return hornclauses_;
}

void AssertCommand::Excecute(CommandProcessor& processor) {
    processor.Assert(hornclauses_);
}
