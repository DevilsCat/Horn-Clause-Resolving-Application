// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Utils.h"
#include "InputHandler.h"
#include "ProgramException.h"
#include "OutputHandler.h"

#define MAX_ARGS                2
#define PROGRAM_POS             0
#define NUM_HORNCLAUSE_POS      1
#define NO_ERROR                0

#define PRINT_USAGE_RETURN(X) \
    do { \
        std::cout << "Usage: " << argv[PROGRAM_POS] << " <Number of Horn Clause> " << std::endl; \
        return X; \
    } while (0)

int main(int argc, char** argv)
{
    int num_hornclauses = DEFAULT_NUM_HORNCLAUSE;
    
    if (argc > MAX_ARGS) {  // Numbers of arguments not satisfied.
        PRINT_USAGE_RETURN(EXIT_FAILURE);
    }
    
    if (argc == MAX_ARGS) {  // The second should always be positive number.
        if (is_number(argv[NUM_HORNCLAUSE_POS]) && 0 != atoi(argv[NUM_HORNCLAUSE_POS]))
            num_hornclauses = atoi(argv[NUM_HORNCLAUSE_POS]);
        else
            PRINT_USAGE_RETURN(EXIT_FAILURE);
    }

    // Initialize some necessary stuffs here.
	srand(time(nullptr));
    InputHandler::init(std::cin);
    OutputHandler::init(std::cout);
    SymbolTable::init();
    HornclauseDatabase::init(*SymbolTable::instance());
    CommandProcessor::init(num_hornclauses);

    // Read input and make command
    int error_code;
    OutputHandler::instance()->DisplayProgram([](const short&){});  // Print out the empty template.
    while (true) {
        try {
            OutputHandler::instance()->DisplayPrompt();
            std::string cmd_str = InputHandler::instance()->GetInputFromStream();
            std::shared_ptr<Command> command = InputHandler::instance()->MakeCommand(cmd_str);
            if (command)
                command->Excecute(*CommandProcessor::instance());
        }
        catch (ProgramException& e) {
            OutputHandler::instance()->DisplayHint(e.what());
            // Unrecoverable error
            if (e.code() == ProgramException::kFatalError) {
                error_code = e.code();
                break;
            }
        }
    }
    return error_code;
}

