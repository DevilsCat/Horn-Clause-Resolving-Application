#include "stdafx.h"
#include "ProcessCommand.h"

void ProcessCommand::Excecute(CommandProcessor& processor) {
    processor.Process(filename_);
}

ProcessCommand::ProcessCommand(const std::string& filename) :
    filename_(filename)
{}