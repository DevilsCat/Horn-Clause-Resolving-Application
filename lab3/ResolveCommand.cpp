#include "stdafx.h"
#include "ResolveCommand.h"

ResolveCommand::ResolveCommand(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause) :
    num_first_hornclause_(num_first_hornclause), num_second_hornclause_(num_second_hornclause)
{}

unsigned ResolveCommand::num_first_hornclause() {
    return num_first_hornclause_;
}

unsigned ResolveCommand::num_second_hornclause() {
    return num_second_hornclause_;
}

void ResolveCommand::Excecute(CommandProcessor& processor) {
    processor.Resolve(num_first_hornclause_, num_second_hornclause_);
}