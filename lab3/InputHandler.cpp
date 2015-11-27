// InputHanlder.cpp -- this file defines Inputhandler Class for {Command Processor Pattern} 
// which receives and process command
// Created by Yu Xiao, Anqi Zhang, all right reserved.
#include "stdafx.h"
#include "InputHandler.h"
#include "Utils.h"
#include <sstream>
#include "ProgramException.h"

// initialize the static member function.
std::shared_ptr<InputHandler> InputHandler::input_handler_ = nullptr;
std::once_flag InputHandler::init_flag_;

std::shared_ptr<InputHandler> InputHandler::instance() {
    if (input_handler_ == nullptr)
        throw ProgramException("InputHanlder not initialized.", ProgramException::kFatalError);
    return input_handler_;
}

void InputHandler::init(std::istream& is) {
    std::call_once(init_flag_, [&is](){ input_handler_ = std::shared_ptr<InputHandler>(new InputHandler(is)); });
}

InputHandler::InputHandler(std::istream& is) :
    is_(is)
{}

std::string InputHandler::GetInputFromStream() const {
    std::string line;
    getline(is_, line);
    return line;
}

std::shared_ptr<Command> InputHandler::MakeCommand(const std::string& command) const {
    if (command.empty()) { return nullptr; }  // skip the empty line.
    std::istringstream iss(command);  // make string as an istream so that we can use operator>>
    std::string cmd_type;
    std::string cmd_descript;
    iss >> cmd_type >> std::ws;  // std::ws remove all successive redundant white space.
    getline(iss, cmd_descript);

    switch (CheckCommandType_(cmd_type)) {
    case Command::kProcess:   { return MakeProcessCommand_(cmd_descript); }
    case Command::kAssert:    { return MakeAssertCommand_(cmd_descript); }
    case Command::kUp:        { return MakeUpCommand_(cmd_descript); }
    case Command::kDown:      { return MakeDownCommand_(cmd_descript); }
    case Command::kResolve:   { return MakeResolveCommand_(cmd_descript); }
    case Command::kRandomize: { return MakeRandomizeCommand_(cmd_descript); }
    case Command::kSet:       { return MakeSetCommand_(cmd_descript); }
    case Command::kPrint:     { return MakePrintCommand_(cmd_descript); }
    case Command::kUnknown: 
    default:                  { return nullptr; }
    }
}

Command::CommandType InputHandler::CheckCommandType_(const std::string& command) {
    if (command == "process")   { return Command::kProcess; }
    if (command == "assert")    { return Command::kAssert; }
    if (command == "up")        { return Command::kUp; }
    if (command == "down")      { return Command::kDown; }
    if (command == "resolve")   { return Command::kResolve; }
    if (command == "randomize") { return Command::kRandomize; }
    if (command == "set")       { return Command::kSet; }
    if (command == "print")     { return Command::kPrint; }
    return Command::kUnknown;
}

std::shared_ptr<Command> InputHandler::MakeProcessCommand_(const std::string& descript) {
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

std::shared_ptr<Command> InputHandler::MakeAssertCommand_(const std::string& descript) {
    if (descript.empty())
        throw ProgramException(
        "Assert Command Error: Not Enough Arguments.",
        ProgramException::kNumberArgsMisMatch
        );
    return std::make_shared<AssertCommand>(descript);
}

std::shared_ptr<Command> InputHandler::MakeUpCommand_(const std::string& descript) {
    const unsigned kNumParams = 1;
    const unsigned kOptionalNLinePos = 0;

    std::vector<std::string> params = Tokenize(descript);
    if (params.size() > kNumParams)
        throw ProgramException(
        "Up Command Error: Arguments Number Mismatch.",
        ProgramException::kNumberArgsMisMatch
        );
    if (params.size() == kNumParams) {
        if (!is_number(params[kOptionalNLinePos]))
            throw ProgramException(
            "Up Command Error: Invalid Numeric Input.",
            ProgramException::kInvalidNumber
            );
        return std::make_shared<UpCommand>(to_number(params[kOptionalNLinePos]));
    }
    return std::make_shared<UpCommand>();
}

std::shared_ptr<Command> InputHandler::MakeDownCommand_(const std::string& descript) {
    const unsigned kNumParams = 1;
    const unsigned kOptionalNLinePos = 0;

    std::vector<std::string> params = Tokenize(descript);
    if (params.size() > kNumParams)
        throw ProgramException(
        "Down Command Error: Arguments Number Mismatch.",
        ProgramException::kNumberArgsMisMatch
        );
    if (params.size() == kNumParams) {
        if (!is_number(params[kOptionalNLinePos]))
            throw ProgramException(
            "Down Command Error: Invalid Numeric Input.",
            ProgramException::kInvalidNumber
            );
        return std::make_shared<DownCommand>(to_number(params[kOptionalNLinePos]));
    }
    return std::make_shared<DownCommand>();
}

std::shared_ptr<Command> InputHandler::MakeResolveCommand_(const std::string& descript) {
    const unsigned kNumParams = 2;
    const unsigned kFirstNumPos = 0;
    const unsigned kSecondNumPos = 1;
    
    std::vector<std::string> params = Tokenize(descript);
    if (params.size() != kNumParams || !is_number(params[kFirstNumPos]) || !is_number(params[kSecondNumPos]))
        throw ProgramException(
            "Resolve Command Error: Unexpeted Numberic Input",
            ProgramException::kInvalidNumber
        );
    return std::make_shared<ResolveCommand>(to_number(params[kFirstNumPos]), 
                                            to_number(params[kSecondNumPos]));
}

std::shared_ptr<Command> InputHandler::MakeRandomizeCommand_(const std::string& descript) {
    const unsigned kMaxNumParams = 2;
    const unsigned kVariablePos = 0;
    const unsigned kOptionalMaxPos = 1;

    std::vector<std::string> params = Tokenize(descript);
    if (params.empty() || params.size() > kMaxNumParams) {
        throw ProgramException(
            "Randomized Command Error: Not Enough Arguments.",
            ProgramException::kNumberArgsMisMatch
        );
    } 
    if (!is_variable(params[kVariablePos])) {
        throw ProgramException(
            "Randomized Command Error: Invalid Alphabetic Variable.",
            ProgramException::kInvalidVariable
        );
    }
    std::string varaible(params[kVariablePos]);
    if (params.size() == kMaxNumParams) {
        if (is_number(params[kOptionalMaxPos])) {
            unsigned max_i = to_number(params[kOptionalMaxPos]);
            return std::make_shared<RandomizeCommand>(varaible, max_i);
        }
        throw ProgramException(
            "Randomized Command Error: Unexpected Numeric Input.",
            ProgramException::kInvalidNumber
        );
    }
    return std::make_shared<RandomizeCommand>(varaible);
}

std::shared_ptr<Command> InputHandler::MakeSetCommand_(const std::string& descript) {
    const unsigned kNumParams = 2;
    const unsigned kVariablePos = 0;
    const unsigned kValuePos = 1;

    std::vector<std::string> params = Tokenize(descript);
    if (params.size() != kNumParams)
        throw ProgramException(
            "Set Command Error: Arguments Number Mismatch.",
            ProgramException::kNumberArgsMisMatch
        );
    if (!is_number(params[kValuePos]))
        throw ProgramException(
            "Set Command Error: Unexpected Numeric Input.",
            ProgramException::kInvalidNumber
        );
    if (!is_variable(params[kVariablePos])) {
        throw ProgramException(
            "Randomized Command Error: Invalid Alphabetic Variable.",
            ProgramException::kInvalidVariable
            );
    }
    return std::make_shared<SetCommand>(params[kVariablePos], 
                                        to_number(params[kValuePos]));
}

std::shared_ptr<Command> InputHandler::MakePrintCommand_(const std::string& descript) {
    if (!descript.empty())
        throw ProgramException(
            "Print Command Error: Arguments Number Mismatch.",
            ProgramException::kNumberArgsMisMatch
        );
    return std::make_shared<PrintCommand>();
}