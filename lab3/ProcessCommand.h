#ifndef PROCESS_COMMAND_H
#define PROCESS_COMMAND_H
#include "Command.h"

class ProcessCommand : public Command {
public:
    explicit ProcessCommand(const std::string& filename);

    virtual void Excecute(CommandProcessor& processor) override;    

private:
    std::string filename_;
};

#endif
