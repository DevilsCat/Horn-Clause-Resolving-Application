#include "stdafx.h"
#include "RandomizeCommand.h"

RandomizeCommand::RandomizeCommand(const std::string& variable, const unsigned& max) :
    variable_(variable), max_(max)
{}

std::string RandomizeCommand::variable() {
    return variable_;
}

unsigned RandomizeCommand::max() {
    return max_;
}

void RandomizeCommand::Excecute(CommandProcessor& processor) {
    processor.Randomize(variable_, max_);
}