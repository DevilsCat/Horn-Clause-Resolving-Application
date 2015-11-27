// InputHanlder.h -- this file declares Inputhandler Class for {Command Processor Pattern} 
// which receives and process command
// Created by Yu Xiao, Anqi Zhang, all right reserved.
#ifndef INPUT_HANDLER_H
#define INPIT_HANDLER_H
#include <istream>
#include <memory>
#include "Commands.h"

// Receives the user input and parses it to associated command. It also validates the user input,
// if not correct it will return ProgramException to indicate the error type.
// Usage Example:
//      InputHandler::init(std::cin);
//      std::string cmd_str = InputHandler::instance()->GetInputFromStream();
//      std::shared_ptr<Command> command = InputHandler::instance()->MakeCommand(cmd_str);
class InputHandler {
public:
    // Returns the singleton of this class.
    static std::shared_ptr<InputHandler> instance();

    // Takes an {istream} object which can "getline" from and initializes the singleton.
    static void init(std::istream&);

    // deletes function to ensure the class uncopiable.
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator= (const InputHandler&) = delete;

    // Reads a line from stored {istream} and returns a {string} of this line.
    std::string GetInputFromStream() const;

    // Returns a smart pointer of command family by given command string.
    std::shared_ptr<Command> MakeCommand(const std::string& command) const;

private:
    // privates the constructor for the Singleton Pattern.
    explicit InputHandler(std::istream& is);

    // Returns {CommandType} given a command type string.
    static Command::CommandType CheckCommandType_(const std::string& command);

    // Makes a {ProcessCommand} object, throws a {ProgramException::kNumberArgsMisMatch}
    // exception if make fails.
    static std::shared_ptr<Command> MakeProcessCommand_(const std::string& descript);

    // Makes an {AssertCommand} object, throws a {ProgramException::kNumberArgsMisMatch}
    // exception if make failes.
    static std::shared_ptr<Command> MakeAssertCommand_(const std::string& descript);

    // Makes an {UpCommand} object, throws a {ProgramException::kNumberArgsMisMatch} or
    // {ProgramException::kInvalidNumber} exception if make fails.
    static std::shared_ptr<Command> MakeUpCommand_(const std::string& descript);

    // Makes a {DownCommand} object, throws a {ProgramException::kNumberArgsMisMatch} or
    // {ProgramException::kInvalidNumber} exception if make fails.
    static std::shared_ptr<Command> MakeDownCommand_(const std::string& descript);

    // Makes a {ResolveCommand} object, throws a {ProgramException::kInvalidNumber} 
    // if make fails.
    static std::shared_ptr<Command> MakeResolveCommand_(const std::string& descript);

    // Makes a {RandomizeCommand} object, throws a {ProgramException::kNumberArgsMisMatch} or
    // {ProgramException::kInvalidVariable} if make fails.
    static std::shared_ptr<Command> MakeRandomizeCommand_(const std::string& descript);

    // Makes a {SetCommand} object, throws {ProgramException::kNumberArgsMisMatch} or
    // {ProgramException::kInvalidNumber} or {ProgramException::kInvalidVariable} if
    // make fails.
    static std::shared_ptr<Command> MakeSetCommand_(const std::string& descript);

    // Make a {PrintCommand} object, throws {ProgramException::kNumberArgsMisMatch}
    // if make fails.
    static std::shared_ptr<Command> MakePrintCommand_(const std::string& descript);

    // Stores an {istream} to "getline" on.
    std::istream& is_;

    // Stores the singleton of this class
    static std::shared_ptr<InputHandler> input_handler_;

    // Ensures init() only make effect once.
    static std::once_flag init_flag_;
};

#endif
