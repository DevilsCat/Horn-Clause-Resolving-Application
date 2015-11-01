﻿#include "stdafx.h"
#include <iostream>
#include "CommandProcessor.h"
#include "parser.h"
#include "ProgramException.h"
#include "PrintVisitor.h"
#include "SymbolTable.h"
#include "DeductiveDatabase.h"

CommandProcessor::CommandProcessor() {}

CommandProcessor::~CommandProcessor() {}

void CommandProcessor::Process(const std::string& filename) {
    std::cout << "Process Command with " << filename << std::endl;
    Parser parser(filename);
    int ret = parser.Parse();
    if (ret) {
        throw ProgramException(
            "Parsing File Failed", 
            ProgramException::ExceptionCode(ret)
        );
    }
    std::shared_ptr<RootNode> root = parser.root();
    PrintVisitor visitor;
    root->Accept(visitor);
    SymbolTable st;
    st.Fill(root);
    st.Print(std::cout); 
    DeductiveDatabase database(st);
    root->Accept(database);
    database.Display(std::cout, 0, database.size());
}

void CommandProcessor::Assert(const std::string& hornclauses) {
    std::cout << "Assert Command with " << hornclauses << std::endl;
}

void CommandProcessor::Up(const unsigned& nlines) {
    std::cout << "Up Command with " << nlines << std::endl;
}

void CommandProcessor::Down(const unsigned& nlines) {
    std::cout << "Down Command with " << nlines << std::endl;
}

void CommandProcessor::Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause) {
    std::cout << "Resolve Command with " << "{" << num_first_hornclause << "," << num_second_hornclause << "}" << std::endl;
}

void CommandProcessor::Randomize(const std::string& variable, const unsigned& max) {
    std::cout << "Randomize Command with " << variable << " with maximum " << max << std::endl;
}

void CommandProcessor::Set(const std::string& variable, const int& value) {
    std::cout << "Set Command with " << variable << " with value " << value << std::endl;
}

void CommandProcessor::Print() {
    std::cout << "Print Command" << std::endl;
}