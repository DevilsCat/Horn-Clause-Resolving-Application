#pragma once
#include "Command.h"

class SetCommand : public Command {
public:
    
    SetCommand(const std::string& variable, const unsigned& value);

    std::string variable();

    unsigned value();

    virtual void Excecute(CommandProcessor& processor) override;
private:
    std::string variable_;

    unsigned value_;
};
