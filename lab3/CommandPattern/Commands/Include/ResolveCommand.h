#pragma once
#include "Command.h"

class ResolveCommand : public Command {
public:
    ResolveCommand(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause);

    unsigned num_first_hornclause();

    unsigned num_second_hornclause();

    virtual void Excecute(CommandProcessor& processor) override;

private:
    unsigned num_first_hornclause_;
    
    unsigned num_second_hornclause_;
};
