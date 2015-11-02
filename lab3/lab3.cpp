// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Utils.h"
#include "Command.h"

#define MAX_ARGS                2
#define PROGRAM_POS             0
#define NUM_HORNCLAUSE_POS      1
#define DEFAULT_NUM_HORNCLAUSE  10
#define NO_ERROR                0
#include "InputHandler.h"
#include "ProgramException.h"

int main(int argc, char** argv)
{
    unsigned num_hornclauses = DEFAULT_NUM_HORNCLAUSE;
    
    if (argc > MAX_ARGS) {
        std::cout << "Usage : " << argv[PROGRAM_POS] << " <Number of Horn Clause> " << std::endl;
        return EXIT_FAILURE;
    }
    
    if (argc == MAX_ARGS) {
        if (IsNumber(argv[NUM_HORNCLAUSE_POS]))
            num_hornclauses = atoi(argv[NUM_HORNCLAUSE_POS]);
        else
            std::cout << "Usage : " << argv[PROGRAM_POS] << " <Number of Honr Clause> " << std::endl;
    }

    // TODO Initialize some necessary stuffs here.
    CommandProcessor cmd_processor;
    InputHandler input_handler(std::cin);

    // TODO Read input and make command
    int error_code = NO_ERROR;
    while (true) {
        try {
            std::cout << ">>";
            std::string cmd_str = input_handler.GetInputFromStream();
            std::shared_ptr<Command> command_ptr = input_handler.MakeCommand(cmd_str);
            if (command_ptr)
                command_ptr->Excecute(cmd_processor);
        }
        catch (ProgramException& e) {
            std::cerr << e.what() << " with error code: " << e.code() << std::endl;
            // Unrecoverable error
            if (e.code() == ProgramException::kFatalError) {
                error_code = e.code();
                break;
            }
                
        }
    }
    return error_code;;
}

