#pragma once
#include "Command.h"
#include <string>

class AssertCommand : public Command {
public:
    AssertCommand(const std::string& hornclauses);

    std::string hornclauses();

    virtual void Excecute(CommandProcessor& processor) override;
private:
    std::string hornclauses_;
};
