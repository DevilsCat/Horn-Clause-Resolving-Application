#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "CommandProcessor.h"
#include "parser.h"
#include "ProgramException.h"
#include "SymbolTable.h"
#include "DeductiveDatabase.h"
#include "Unifier.h"
#include "Utils.h"

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

CommandProcessor::CommandProcessor() :
database_(symbol_table_), display_counter_(0), display_num_(DEFAULT_NUM_HORNCLAUSE)
{}

CommandProcessor::CommandProcessor(int num) : 
database_(symbol_table_), display_counter_(0), display_num_(num)
{}

CommandProcessor::~CommandProcessor() {}

void CommandProcessor::Process(const std::string& filename) {
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
    
    symbol_table_.FillEntriesFromTree(root);
    
    database_.FillHornclauseFromTree(root);

    DisplayDatabaseEntries(display_counter_ = 0);  // Re-display the database entries start from top.
}

void CommandProcessor::Assert(const std::string& hornclauses) {
    std::istringstream iss(hornclauses);
    Parser parser(iss);
    int ret = parser.Parse();
    if (ret) {
        throw ProgramException(
            "Parsing Hornclause Sentence Failed",
            ProgramException::ExceptionCode(ret)
            );
    }
    std::shared_ptr<RootNode> root = parser.root();

    symbol_table_.FillEntriesFromTree(root);

    database_.FillHornclauseFromTree(root);
    
    DisplayDatabaseEntries(display_counter_ = 0);
}

void CommandProcessor::Up(const unsigned& nlines) {
    int begin;
    if (nlines != 0) {
        begin = MAX(int(display_counter_ - nlines), 0);
    } else {
        begin = MAX(int(display_counter_ - display_num_), 0);
    }

    DisplayDatabaseEntries(display_counter_ = begin);  // By Yu, I refract this Database Display method, so that we can
                                                       // reuse it in other place, as well as seal the format building procedure.
}

void CommandProcessor::Down(const unsigned& nlines) {
    int begin;
    if (nlines != 0) {
        begin = MIN(display_counter_ + nlines, int(database_.size()));
    } else {
        begin = MIN(display_counter_ + display_num_, int(database_.size()));
    }

    DisplayDatabaseEntries(display_counter_ = begin);
}

void CommandProcessor::Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause) {
    const unsigned kIndexOffset = 1;

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
    
    // Add Hornclause to database.
    for (HornclauseDatabaseEntry hornclause : res) {
        database_.AddHornclauseEntry(hornclause);
    }

    // Print out the database
    DisplayDatabaseEntries(display_counter_ = 0);
}

void CommandProcessor::Randomize(std::string& variable, const unsigned& max) {
    int value = max > 0 ? rand() % max : rand();
    Set(variable, value);
}

void CommandProcessor::Set(std::string& variable, const int& value) {
    const std::string sRegBound = "[[:lower:]]";
    std::regex bound(sRegBound);
    if (!regex_match(variable, bound) || value < 0){ return; }  // The input variable is not in bound format.

    if (!symbol_table_.CheckBound(variable)) {
        symbol_table_.AddBound(variable);
    }
    symbol_table_.SetBound(variable, value);
}

void CommandProcessor::Print() {
    symbol_table_.PrintSt(std::cout);
}

void CommandProcessor::DisplayDatabaseEntries(const unsigned& begin) { 
    Output::DisplayHeader(std::cout);
    std::cout << "////////////////////" << std::endl;
    for (int i = database_.Display(std::cout, begin, display_num_); i < display_num_; i++) {  
        std::cout << std::endl;
    }
    std::cout << "////////////////////" << std::endl;
}

void CommandProcessor::DisplayDatabaseEntriesPredicate(const unsigned& max_nline) {
    
}