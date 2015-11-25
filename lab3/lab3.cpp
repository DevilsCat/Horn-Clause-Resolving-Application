// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Utils.h"
#include "Command.h"
#include "InputHandler.h"
#include "ProgramException.h"

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
    CommandProcessor cmd_processor(num_hornclauses);
    InputHandler input_handler(std::cin);

    // Read input and make command
    int error_code;
    output_handler.DisplayProgram([](const short&){});  // Print out the empty template.
    while (true) {
        try {
            output_handler.DisplayPrompt();
            std::string cmd_str = input_handler.GetInputFromStream();
            std::shared_ptr<Command> command_ptr = input_handler.MakeCommand(cmd_str);
            if (command_ptr)
                command_ptr->Excecute(cmd_processor);
        }
        catch (ProgramException& e) {
            output_handler.DisplayHint(e.what());
            // Unrecoverable error
            if (e.code() == ProgramException::kFatalError) {
                error_code = e.code();
                break;
            }
                
        }
    }
    return error_code;
}

