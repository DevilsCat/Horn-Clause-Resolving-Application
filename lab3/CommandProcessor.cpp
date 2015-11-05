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
        begin = MAX(int(display_counter_ - Output::GetPrintableZoneHeight()), 0);
    }

    DisplayDatabaseEntries(display_counter_ = begin);  // By Yu, I refract this Database Display method, so that we can
                                                       // reuse it in other place, as well as seal the format building procedure.
}

void CommandProcessor::Down(const unsigned& nlines) {
    int begin;
    unsigned scroll_lines = !nlines ? Output::GetPrintableZoneHeight() : nlines;
    if (display_counter_ + scroll_lines >= int(database_.size())) {  // Scrolling out of database size bound.
        begin = display_counter_;
    } else {
        begin = display_counter_ + scroll_lines;
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
    auto Predicate = [this](const unsigned& max_nlines)->unsigned {
        return symbol_table_.PrintSt(std::cout);
    };
    Output::DisplayProgram(std::cout, Predicate);
}

void CommandProcessor::DisplayDatabaseEntries(const unsigned& begin) { 
    auto Predicate = [&begin, this](const unsigned& max_nlines)->unsigned {
        unsigned nlines_display = display_num_ == DEFAULT_NUM_HORNCLAUSE ? max_nlines : display_num_;
        return database_.Display(std::cout, begin, nlines_display);
    };
    Output::DisplayProgram(std::cout, Predicate);
}