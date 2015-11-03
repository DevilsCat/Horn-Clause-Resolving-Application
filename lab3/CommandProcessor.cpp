#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <regex>
#include "CommandProcessor.h"
#include "parser.h"
#include "ProgramException.h"
#include "PrintVisitor.h"
#include "SymbolTable.h"
#include "DeductiveDatabase.h"

#define REG_BOUND "[[:lower:]]"

CommandProcessor::CommandProcessor() :
database_(symbol_table_), DisplayCounter(0)
{}

CommandProcessor::~CommandProcessor() {}

void CommandProcessor::Process(const std::string& filename) {
    std::cout << "Process Command with " << filename << std::endl;
    std::ifstream ifs(filename);
    Parser parser(ifs);
    int ret = parser.Parse();
    if (ret) {
        throw ProgramException(
            "Parsing File Failed", 
            ProgramException::ExceptionCode(ret)
        );
    }
    std::shared_ptr<RootNode> root = parser.root();

    std::cout << "**********Test Parsing Tree Begin**********" << std::endl;
    root->Accept(PrintVisitor());
    symbol_table_.FillEntriesFromTree(root);
    std::cout << "**********Test Parsing Tree End**********" << std::endl;
    std::cout << "**********Test Symbol Table Begin**********" << std::endl;
    symbol_table_.Print(std::cout); 
    std::cout << "**********Test Symbol Table End**********" << std::endl;
    database_.FillHornclauseFromTree(root);
    database_.Display(std::cout, 0, database_.size()); // Now display all.
}

void CommandProcessor::Assert(const std::string& hornclauses) {
    std::cout << "Assert Command with " << hornclauses << std::endl;
    std::istringstream iss(hornclauses);
    Parser parser(iss);
    int ret = parser.Parse();
    if (ret) {
        throw ProgramException(
            "Parsing File Failed",
            ProgramException::ExceptionCode(ret)
            );
    }
    std::shared_ptr<RootNode> root = parser.root();

    std::cout << "**********Test Parsing Tree Begin**********" << std::endl;
    root->Accept(PrintVisitor());
    symbol_table_.FillEntriesFromTree(root);
    std::cout << "**********Test Parsing Tree End**********" << std::endl;
    std::cout << "**********Test Symbol Table Begin**********" << std::endl;
    symbol_table_.Print(std::cout);
    std::cout << "**********Test Symbol Table End**********" << std::endl;
    database_.FillHornclauseFromTree(root);
    database_.Display(std::cout, 0, database_.size()); // Now display all.
}

void CommandProcessor::Up(const unsigned& nlines) {  //FIX
    std::cout << "Up Command with " << nlines << std::endl;
	int rows, begin;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	if (nlines != 0) {
		begin = DisplayCounter - nlines > 0 ? DisplayCounter - nlines : 0;
	} else {
		begin = DisplayCounter - rows > 0 ? DisplayCounter - rows : 0;
	}
	database_.Display(std::cout, begin, DisplayCounter);
	for (int i = DisplayCounter - begin; i < rows-1; ++i){ std::cout << std::endl; }

}

void CommandProcessor::Down(const unsigned& nlines) {
    std::cout << "Down Command with " << nlines << std::endl;
	int rows, end;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	if (nlines != 0) {
		end = DisplayCounter + nlines > database_.size() ? database_.size() : DisplayCounter + nlines;
	}else{
		end = DisplayCounter + rows > database_.size() ? database_.size() : DisplayCounter + rows;
	}
	database_.Display(std::cout, DisplayCounter, end);
	for (int i = end - DisplayCounter; i < rows-1; ++i) { std::cout << std::endl; }

	DisplayCounter = end == database_.size() ? 0 : end;
}

void CommandProcessor::Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause) {
    std::cout << "Resolve Command with " << "{" << num_first_hornclause << "," << num_second_hornclause << "}" << std::endl;
}

void CommandProcessor::Randomize(std::string& variable, const unsigned& max) {
    std::cout << "Randomize Command with " << variable << " with maximum " << max << std::endl;
	std::regex bound(REG_BOUND);
	int value = max > 0 ? rand() % max : rand();
	Set(variable, value);
}

void CommandProcessor::Set(std::string& variable, const int& value) {
    std::cout << "Set Command with " << variable << " with value " << value << std::endl;
	std::regex bound(REG_BOUND);
	if (!std::regex_match(variable, bound) || value < 0){ return; } //simply return

	if (!symbol_table_.CheckBound(variable)) {
		symbol_table_.AddBound(variable);
	}
	symbol_table_.SetBound(variable, value);
}

void CommandProcessor::Print() {
    std::cout << "Print Command" << std::endl;
}