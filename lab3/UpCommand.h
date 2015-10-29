#pragma once
#include "Command.h"

class UpCommand : public Command {
public:
    UpCommand(const unsigned& nlines = 0);

    unsigned nlines();

    virtual void Excecute(CommandProcessor& processor) override;

private:
    unsigned nlines_;
};
