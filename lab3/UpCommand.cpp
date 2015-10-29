#include "stdafx.h"
#include "UpCommand.h"

UpCommand::UpCommand(const unsigned& nlines) :
    nlines_(nlines)
{}

unsigned UpCommand::nlines() {
    return nlines_;
}

void UpCommand::Excecute(CommandProcessor& processor) {
    processor.Up(nlines_);
}