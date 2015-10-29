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
    try {
        std::shared_ptr<Command>command_ptr = input_handler.MakeCommand(std::string("process hornclause.txt"));
        command_ptr->Excecute(cmd_processor);
        command_ptr = input_handler.MakeCommand(std::string("assert ( ( greater a b ) ) ( ( greater 1 x ) ( ( greater 2 y ) ) )"));
        command_ptr->Excecute(cmd_processor);
        command_ptr = input_handler.MakeCommand(std::string("up 10"));
        command_ptr->Excecute(cmd_processor);
        command_ptr = input_handler.MakeCommand(std::string("up"));
        command_ptr->Excecute(cmd_processor);
        command_ptr = input_handler.MakeCommand(std::string("down 10"));
        command_ptr->Excecute(cmd_processor);
        command_ptr = input_handler.MakeCommand(std::string("resolve 1 3"));
        command_ptr->Excecute(cmd_processor);
        //command_ptr = input_handler.MakeCommand(std::string("resolve 1 a")); // broken
        //command_ptr->Excecute(cmd_processor);
        command_ptr = input_handler.MakeCommand(std::string("randomize x 1"));
        command_ptr->Excecute(cmd_processor);
        command_ptr = input_handler.MakeCommand(std::string("set y 2"));
        command_ptr->Excecute(cmd_processor);
        command_ptr = input_handler.MakeCommand(std::string("print"));
        command_ptr->Excecute(cmd_processor);
    } catch (ProgramException& e) {
        std::cerr << e.what() << " error code: " << e.code() << std::endl;
    }
	return 0;
}

