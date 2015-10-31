#include "stdafx.h"
#include "ProcessCommand.h"
#include <iostream>

void ProcessCommand::Excecute(CommandProcessor& processor) {
    processor.Process(filename_);
}

ProcessCommand::ProcessCommand(const std::string& filename) :
    filename_(filename)
{}