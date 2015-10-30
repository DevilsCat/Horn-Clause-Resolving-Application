#include "stdafx.h"
#include "PrintCommand.h"

PrintCommand::PrintCommand() {}

void PrintCommand::Excecute(CommandProcessor& processor) {
    processor.Print();
}