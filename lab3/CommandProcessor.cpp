// CommandProcessor.h -- This file defines CommandProcessor class {CommandProcessor Pattern}.
// Created by Yu Xiao, Anqi Zhang, Copyright preserved.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "CommandProcessor.h"
#include "parser.h"
#include "ProgramException.h"
#include "SymbolTable.h"
#include "HornclauseDatabase.h"
#include "Unifier.h"
#include "Utils.h"

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

// first chance initializes static member function in CommandProcessor class.
std::shared_ptr<CommandProcessor> CommandProcessor::cmd_processor_ = nullptr;
std::once_flag CommandProcessor::init_flag_;

std::shared_ptr<CommandProcessor> CommandProcessor::instance() {
    if (!cmd_processor_) 
        throw ProgramException("CommandProcessor uninitialized.", ProgramException::kFatalError);
    return cmd_processor_;
}

void CommandProcessor::init(const int& num_hornclauses) {
    std::call_once(init_flag_, [&num_hornclauses]() {
        cmd_processor_ = std::shared_ptr<CommandProcessor>(new CommandProcessor(num_hornclauses));
    });
}

CommandProcessor::CommandProcessor(int num) : 
    symbol_table_(*SymbolTable::instance()),
    database_(*HornclauseDatabase::instance()), 
    display_counter_(0), display_num_(num)
{}

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
    DisplayDatabaseEntries_(display_counter_ = 0);  // Re-display the database entries start from top.
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
    DisplayDatabaseEntries_(display_counter_ = 0);
}

void CommandProcessor::Up(const unsigned& nlines) {
    int begin;
    unsigned scroll_lines = nlines ? nlines : GetMaxDisplayNum();  // in nlines is not given, 
                                                                   // display as many as possible.
    begin = MAX(int(display_counter_ - scroll_lines), 0);  // updated begin should be non-negative.

    DisplayDatabaseEntries_(display_counter_ = begin);  // By Yu, I refract this Database Display method, so that we can
                                                        // reuse it in other place, as well as seal the format building procedure.
}

void CommandProcessor::Down(const unsigned& nlines) {
    int begin;
    unsigned scroll_lines = nlines ? nlines : GetMaxDisplayNum();

    begin = display_counter_ + scroll_lines >= int(database_.size()) ?  // Scrolling out of database size bound.
            display_counter_ : display_counter_ + scroll_lines;
    
    DisplayDatabaseEntries_(display_counter_ = begin);
}

void CommandProcessor::Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause) {
    const unsigned kIndexOffset = 1;

    Unifier unifier(symbol_table_);
    HornclauseDatabase::Entry first_hornclause;
    HornclauseDatabase::Entry second_hornclause;
    if (!database_.RetrieveHornclauseEntry(first_hornclause, num_first_hornclause - kIndexOffset) ||
        !database_.RetrieveHornclauseEntry(second_hornclause, num_second_hornclause - kIndexOffset)) {
        throw ProgramException(
            "Cannot Retrieve Hornclause Given Index",
            ProgramException::kInvalidHornclauseIndex
        );
    }
    std::vector<HornclauseDatabase::Entry> res;
    unifier.UnifyHornclauses(res, first_hornclause, second_hornclause);
    
    // Add Hornclause to database.
    for (HornclauseDatabase::Entry hornclause : res) {
        database_.AddHornclauseEntry(hornclause);
    }

    // Print out the database
    DisplayDatabaseEntries_(display_counter_ = 0);
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
    auto Predicate = [this](const short&) {  // Print out the symbol table regardless 
        symbol_table_.Print();             // the available height of windows.
    };
    output_handler.DisplayProgram(Predicate, "Symbol Table Entries");
}

void CommandProcessor::DisplayDatabaseEntries_(const unsigned& begin) { 
    auto Predicate = [&begin, this](const short& max_nlines) {
        unsigned nlines_display =   // actual lines to display, print the full available height if DEFAULT_NUM_HORNCLAUSE set.
            display_num_ == DEFAULT_NUM_HORNCLAUSE ? max_nlines : display_num_;
        database_.Display(begin, nlines_display);
    };
    output_handler.DisplayProgram(Predicate, "Horn Clause Database");
}

short CommandProcessor::GetMaxDisplayNum() const {
    return display_num_ != DEFAULT_NUM_HORNCLAUSE ? display_num_ : output_handler.GetPrintableZoneHeight();
}