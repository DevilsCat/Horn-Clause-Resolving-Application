#pragma once
#include "Command.h"

class PrintCommand : public Command {
public:
    PrintCommand();

    virtual void Excecute(CommandProcessor& processor) override;
};
