#pragma once
#include <istream>
#include "Commands.h"
#include <memory>

class InputHandler {
public:
    explicit InputHandler(std::istream& is);

    InputHandler(const InputHandler&) = delete;
    InputHandler& operator= (const InputHandler&) = delete;

    std::string GetInputFromStream();

    std::shared_ptr<Command> MakeCommand(const std::string& command);

private:
    Command::CommandType CheckCommandType(const std::string& command);

    std::shared_ptr<Command> MakeProcessCommand(const std::string& descript);

    std::shared_ptr<Command> MakeAssertCommand(const std::string& descript);

    std::shared_ptr<Command> MakeUpCommand(const std::string& descript);

    std::shared_ptr<Command> MakeDownCommand(const std::string& descript);

    std::shared_ptr<Command> MakeResolveCommand(const std::string& descript);

    std::shared_ptr<Command> MakeRandomizeCommand(const std::string& descript);

    std::shared_ptr<Command> MakeSetCommand(const std::string& descript);

    std::shared_ptr<Command> MakePrintCommand(const std::string& descript);

    std::istream& is_;
};
