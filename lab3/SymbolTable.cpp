// symbol_table.h -- Implements a Symbol Table class that stores variables, constants and predicates showing up
// in the input file.
// Created by Yu Xiao, Anqi Zhang
//
#include "stdafx.h"
#include "SymbolTable.h"
#include "RootNode.h"
#include "SymbolNode.h"
#include "NameNode.h"
#include <iostream>
#include <algorithm>
#include "ProgramException.h"
#include "Utils.h"

SymbolTable::SymbolTable() :
    entry_buffer_pointer_(nullptr)
{}

SymbolTable::~SymbolTable() {}

void SymbolTable::Fill(std::shared_ptr<RootNode> root) {
    root->Accept(*this);
}

void SymbolTable::InsertIdentifier(const BaseToken& token) {
    switch (token.type) {
    case BaseToken::BOUND:   bounds_.insert(dynamic_cast<const BoundToken&>(token));     break;
    case BaseToken::UNBOUND: unbounds_.insert(dynamic_cast<const UnBoundToken&>(token)); break;
    case BaseToken::NUMBER:  constants_.insert(dynamic_cast<const NumberToken&>(token)); break;
    default:                                                                             break;
    }
}

void SymbolTable::InsertPredicate(const PredicateEntry& p_entry) {
    if (ISPredicateEntryDup(p_entry)) {
        std::cout << "Skipped Duplicated Predicate Entry : " << p_entry << std::endl;
        return;
    }
    // Populate Predicate Entry.
    const std::string p_name = p_entry.name;
    if (!preds_map_.count(p_name)) {
        preds_map_[p_name] = std::vector<PredicateEntry>();
    }
    preds_map_[p_name].push_back(p_entry);
}

const BaseToken& SymbolTable::FindIdentifier(const BaseToken& identifer) {
    switch (identifer.type) {
    case BaseToken::BOUND:   return *find_if(bounds_.begin(), bounds_.end(), TokenFinder(identifer));
    case BaseToken::UNBOUND: return *find_if(unbounds_.begin(), unbounds_.end(), TokenFinder(identifer));
    case BaseToken::NUMBER:  return *find_if(constants_.begin(), constants_.end(), TokenFinder(identifer));
    default:                 throw ProgramException("Cannot Find Identifier From SymbolTable", ProgramException::kFatalError);
    }
}

bool SymbolTable::ISPredicateEntryDup(const PredicateEntry& p) {
    if (!preds_map_.count(p.name)) { return false; } // no name inside the map.
    const std::vector<PredicateEntry>& predicates = preds_map_[p.name];
    for (const PredicateEntry& predicate : predicates) {
        if (predicate.EqualsTo(p)) { return true; }
    }
    return false;
}

void SymbolTable::Print(std::ostream& os) const {
    os << "UnBound Label : " << std::endl;
    for (const UnBoundToken& unbound : unbounds_) {
        os << Encode(unbound);
    }
    os << std::endl << "Bound Label : " << std::endl;
    for (const BoundToken& bound : bounds_) {
        os << Encode(bound);
    }
    os << std::endl << "Constants Number : " << std::endl;
    for (const NumberToken& constant : constants_) {
        os << Encode(constant);
    }
    os << std::endl << "Predicate : " << std::endl;
    for (auto str_entries_pair: preds_map_) {
        auto entries = str_entries_pair.second;
        for (auto p_entry : entries)
            os << p_entry << std::endl;
    }
}

void SymbolTable::OnPreVisit(PredicateNode*) {
    entry_buffer_pointer_ = new PredicateEntry();
}

void SymbolTable::OnPostVisit(PredicateNode*) {
    InsertPredicate(*entry_buffer_pointer_);
    delete entry_buffer_pointer_;
}

void SymbolTable::OnVisit(SymbolNode* node_ptr) {
    InsertIdentifier(*node_ptr->symbol_ptr_);
}

void SymbolTable::OnPostVisit(SymbolNode* node_ptr) {
    entry_buffer_pointer_->symbols.push_back(&FindIdentifier(*node_ptr->symbol_ptr_));
}

void SymbolTable::OnVisit(NameNode* node_ptr) {
    entry_buffer_pointer_->name = static_cast<std::string>(*(node_ptr->label_ptr_));
}



/////////////////// Here is For PredicateEntry. /////////////////////////

PredicateEntry::PredicateEntry() {}

PredicateEntry::PredicateEntry(const LabelToken& name_) : name(name_) {}

bool PredicateEntry::EqualsTo(const PredicateEntry& that) const{
    if (name != that.name)                     { return false; }
    if (symbols.size() != that.symbols.size()) { return false; }

    std::vector<const BaseToken*>::const_iterator this_it = symbols.begin();
    std::vector<const BaseToken*>::const_iterator that_it = that.symbols.begin();

    for (; this_it != symbols.end(); ++this_it, ++that_it) {
        if (**this_it != **that_it) { return false; }
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const PredicateEntry& p) {
    os << Encode(p.name);
    for (const BaseToken* symbol_ptr : p.symbols) {
        if (symbol_ptr->type == BaseToken::BOUND) os << Encode(*dynamic_cast<const BoundToken*>(symbol_ptr));
        else                                      os << Encode(*symbol_ptr);
    }
    return os;
}