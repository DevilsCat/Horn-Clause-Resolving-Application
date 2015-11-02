#pragma once
#include "Command.h"

class DownCommand : public Command {
public:
    DownCommand(const unsigned& nlines = 0);

    unsigned nlines();

    virtual void Excecute(CommandProcessor& processor) override;

private:
    unsigned nlines_;
};
