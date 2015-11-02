#include "stdafx.h"
#include "SetCommand.h"

SetCommand::SetCommand(const std::string& variable, const unsigned& value) :
    variable_(variable), value_(value)
{}

std::string SetCommand::variable() {
    return variable_;
}

unsigned SetCommand::value() {
    return value_;
}

void SetCommand::Excecute(CommandProcessor& processor) {
    processor.Set(variable_, value_);
}