#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "CommandProcessor.h"
#include "parser.h"
#include "ProgramException.h"
#include "PrintVisitor.h"
#include "SymbolTable.h"
#include "DeductiveDatabase.h"
#include "Unifier.h"

CommandProcessor::CommandProcessor() :
    database_(symbol_table_)
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

void CommandProcessor::Up(const unsigned& nlines) {
    std::cout << "Up Command with " << nlines << std::endl;
}

void CommandProcessor::Down(const unsigned& nlines) {
    std::cout << "Down Command with " << nlines << std::endl;
}

void CommandProcessor::Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause) {
    const unsigned kIndexOffset = 1;
    std::cout << "Resolve Command with " << "{" << num_first_hornclause << "," << num_second_hornclause << "}" << std::endl;
    Unifier unifier(symbol_table_);
    HornclauseDatabaseEntry first_hornclause;
    HornclauseDatabaseEntry second_hornclause;
    if (!database_.RetrieveHornclauseEntry(first_hornclause, num_first_hornclause - kIndexOffset) ||
        !database_.RetrieveHornclauseEntry(second_hornclause, num_second_hornclause - kIndexOffset)) {
        throw ProgramException(
            "Cannot Retrieve Hornclause Given Index",
            ProgramException::kInvalidHornclauseIndex
        );
    }
    std::vector<HornclauseDatabaseEntry> res;
    unifier.UnifyHornclauses(res, first_hornclause, second_hornclause);
    
    // Added Hornclause to database.
    for (HornclauseDatabaseEntry hornclause : res) {
        database_.AddHornclauseEntry(hornclause);
    }

    // Print Out For Debug
    symbol_table_.Print(std::cout);
    database_.Display(std::cout, 0, database_.size()); // Now display all.
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