#include "stdafx.h"
#include "InputHandler.h"
#include "UpCommand.h"
#include "Utils.h"
#include "AssertCommand.h"
#include "ProcessCommand.h"
#include <sstream>
#include "DownCommand.h"
#include "ResolveCommand.h"
#include "ProgramException.h"
#include "RandomizeCommand.h"
#include "SetCommand.h"
#include "PrintCommand.h"

InputHandler::InputHandler(std::istream& is) :
    is_(is)
{}

std::shared_ptr<Command> InputHandler::MakeCommand(const std::string& command) {
    if (command.empty()) { return std::shared_ptr<Command>(); }
    std::istringstream iss(command);
    std::string cmd_type;
    std::string cmd_descript;
    iss >> cmd_type >> std::ws;
    getline(iss, cmd_descript);

    switch (CheckCommandType(cmd_type)) {
    case Command::kProcess:
        return MakeProcessCommand(cmd_descript);
    case Command::kAssert:
        return MakeAssertCommand(cmd_descript);
    case Command::kUp:
        return MakeUpCommand(cmd_descript);
    case Command::kDown:
        return MakeDownCommand(cmd_descript);
    case Command::kResolve:
        return MakeResolveCommand(cmd_descript);
    case Command::kRandomize:
        return MakeRandomizeCommand(cmd_descript);
    case Command::kSet: 
        return MakeSetCommand(cmd_descript);
    case Command::kPrint: 
        return std::make_shared<PrintCommand>();
    case Command::kUnknown: 
        return nullptr;
    default: break;
    }

    return std::shared_ptr<Command>();
}

std::shared_ptr<Command> InputHandler::MakeProcessCommand(const std::string& descript) {
    const unsigned kNumParams = 1;
    const unsigned kFileNamePos = 0;

    std::vector<std::string> params = Tokenize(descript);

    if (params.size() != kNumParams)
        throw ProgramException(
            "Process Command Error: Argument Numbers Mismatch.",
            ProgramException::kNumberArgsMisMatch
        );

    return std::make_shared<ProcessCommand>(params[kFileNamePos]);
}

std::shared_ptr<Command> InputHandler::MakeAssertCommand(const std::string& descript) {
    if (descript.empty())
        throw ProgramException(
            "Assert Command Error: Not Enough Arguments.",
            ProgramException::kNumberArgsMisMatch
        );
    return std::make_shared<AssertCommand>(descript);
}

std::shared_ptr<Command> InputHandler::MakeUpCommand(const std::string& descript) {
    const unsigned kNumParams = 1;
    const unsigned kOptionalNLinePos = 0;

    std::vector<std::string> params = Tokenize(descript);

    if (params.size() > kNumParams)
        throw ProgramException(
            "Up Command Error: Arguments Number Mismatch.",
            ProgramException::kNumberArgsMisMatch
        );
    if (params.size() == kNumParams) {
        if (!IsNumber(params[kOptionalNLinePos]))
            throw ProgramException(
                "Up Command Error: Invalid Numeric Input.",
                ProgramException::kInvalidNumber
            );
        return std::make_shared<UpCommand>(ToNumber(params[kOptionalNLinePos]));
    }

    return std::make_shared<UpCommand>();
}

std::shared_ptr<Command> InputHandler::MakeDownCommand(const std::string& descript) {
    const unsigned kNumParams = 1;
    const unsigned kOptionalNLinePos = 0;

    std::vector<std::string> params = Tokenize(descript);

    if (params.size() > kNumParams)
        throw ProgramException(
        "Down Command Error: Arguments Number Mismatch.",
        ProgramException::kNumberArgsMisMatch
        );
    if (params.size() == kNumParams) {
        if (!IsNumber(params[kOptionalNLinePos]))
            throw ProgramException(
            "Down Command Error: Invalid Numeric Input.",
            ProgramException::kInvalidNumber
            );
        return std::make_shared<DownCommand>(ToNumber(params[kOptionalNLinePos]));
    }

    return std::make_shared<DownCommand>();
}

Command::CommandType InputHandler::CheckCommandType(const std::string& command) {
    if (command == "process") {
        return Command::kProcess;
    }
    if (command == "assert") {
        return Command::kAssert;
    }
    if (command == "up") {
        return Command::kUp;
    }
    if (command == "down") {
        return Command::kDown;
    }
    if (command == "resolve") {
        return Command::kResolve;
    }
    if (command == "randomize") {
        return Command::kRandomize;
    }
    if (command == "set") {
        return Command::kSet;
    }
    if (command == "print") {
        return Command::kPrint;
    }
    return Command::kUnknown;
}

std::shared_ptr<Command> InputHandler::MakeResolveCommand(const std::string& descript) {
    const unsigned kNumParams = 2;
    const unsigned kFirstNumPos = 0;
    const unsigned kSecondNumPos = 1;
    
    std::vector<std::string> params = Tokenize(descript);

    if (params.size() != kNumParams || !IsNumber(params[kFirstNumPos]) || !IsNumber(params[kSecondNumPos]))
        throw ProgramException(
            "Resolve Command Error: Unexpeted Numberic Input",
            ProgramException::kInvalidNumber
        );

    unsigned first_num = ToNumber(params[kFirstNumPos]);
    unsigned second_num = ToNumber(params[kSecondNumPos]);
    
    return std::make_shared<ResolveCommand>(first_num, second_num);
}

std::shared_ptr<Command> InputHandler::MakeRandomizeCommand(const std::string& descript) {
    const unsigned kMaxNumParams = 2;
    const unsigned kVariableNumPos = 0;
    const unsigned kOptionalMaxPos = 1;

    std::vector<std::string> params = Tokenize(descript);

    if (params.size() > kMaxNumParams) {
        throw ProgramException(
            "Randomized Command Error: Not Enough Arguments.",
            ProgramException::kNumberArgsMisMatch
        );
    } 

    std::string varaible(params[kVariableNumPos]);
    if (params.size() == kMaxNumParams) {
        if (IsNumber(params[kOptionalMaxPos])) {
            unsigned max_i = ToNumber(params[kOptionalMaxPos]);
            return std::make_shared<RandomizeCommand>(varaible, max_i);
        }
        throw ProgramException(
            "Randomized Command Error: Unexpected Numeric Input.",
            ProgramException::kInvalidNumber
        );
    }

    return std::make_shared<RandomizeCommand>(varaible);
}

std::shared_ptr<Command> InputHandler::MakeSetCommand(const std::string& descript) {
    const unsigned kNumParams = 2;
    const unsigned kVariablePos = 0;
    const unsigned kValuePos = 1;

    std::vector<std::string> params = Tokenize(descript);

    if (params.size() != kNumParams)
        throw ProgramException(
            "Set Command Error: Arguments.",
            ProgramException::kNumberArgsMisMatch
        );
    if (!IsNumber(params[kValuePos]))
        throw ProgramException(
            "Set Command Error: Unexpected Numeric Input.",
            ProgramException::kInvalidNumber
        );

    std::string variable = params[kVariablePos];
    unsigned value = ToNumber(params[kValuePos]);

    return std::make_shared<SetCommand>(variable, value);
}