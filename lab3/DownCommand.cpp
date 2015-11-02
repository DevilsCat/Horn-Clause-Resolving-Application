#include "stdafx.h"
#include "DownCommand.h"

DownCommand::DownCommand(const unsigned& nlines) :
    nlines_(nlines)
{}

unsigned DownCommand::nlines() {
    return nlines_;
}

void DownCommand::Excecute(CommandProcessor& processor) {
    processor.Down(nlines_);
}