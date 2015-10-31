#pragma once
#include "Command.h"

class RandomizeCommand : public Command {
public:
    RandomizeCommand(const std::string& variable, const unsigned& max = 0);

    std::string variable();

    unsigned max();

    virtual void Excecute(CommandProcessor& processor) override;

private:
    std::string variable_;

    unsigned max_;
};
