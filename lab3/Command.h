#ifndef COMMAND_H
#define COMMAND_H
#include "CommandProcessor.h"

class Command {
public:
    enum CommandType {
        kProcess = 0,
        kAssert,
        kUp,
        kDown,
        kResolve,
        kRandomize,
        kSet,
        kPrint,
        kUnknown
    };

    virtual ~Command();
    
    virtual void Excecute(CommandProcessor& processor) = 0;

};

#endif
