// symbol_table.h -- Implements a Symbol Table class that stores variables, constants and predicates showing up
// in the input file.
// Created by Yu Xiao, Anqi Zhang
//
#include "stdafx.h"
#include "SymbolTable.h"
#include "RootNode.h"
#include "SymbolNode.h"
#include "PredicateNode.h"
#include "NameNode.h"
#include <iostream>
#include <algorithm>
#include "ProgramException.h"
#include "Utils.h"

SymbolTable::SymbolTable() :
    entry_buffer_pointer_(nullptr)
{}

SymbolTable::~SymbolTable() {}

void SymbolTable::FillEntriesFromTree(std::shared_ptr<RootNode> root) {
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

PredicateEntry& SymbolTable::InsertPredicate(const PredicateEntry& p_entry) {
    if (ISPredicateEntryDup(p_entry)) { return *FindPredicateEntryByPredicateEntry(p_entry); }

    // Populate Predicate Entry.
    const std::string p_name = p_entry.name;
    if (!preds_map_.count(p_name)) {
        preds_map_[p_name] = std::list<PredicateEntry>();
    }
    std::list<PredicateEntry>& entries = preds_map_[p_name];
    entries.push_back(p_entry);
    // Log the insertion to trace.
    predicates_trace_.push_back(&entries.back());
    // Return new insertion back to caller, so that both SymbolTable and client can
    // keep consistent.
    return entries.back();
}

const BaseToken& SymbolTable::FindIdentifierByToken(BaseToken& identifer) {
    switch (identifer.type) {
    case BaseToken::BOUND:   return *find_if(bounds_.begin(), bounds_.end(), TokenFinder(identifer));
    case BaseToken::UNBOUND: return *find_if(unbounds_.begin(), unbounds_.end(), TokenFinder(identifer));
    case BaseToken::NUMBER:  return *find_if(constants_.begin(), constants_.end(), TokenFinder(identifer));
    default:                 throw ProgramException("Cannot Find Identifier From SymbolTable", ProgramException::kFatalError);
    }
}

PredicateEntry* SymbolTable::FindPredicateEntryByNode(const PredicateNode& node) {
    return FindPredicateEntryByPredicateEntry(*node.ToPredicateEntry());
}

PredicateEntry* SymbolTable::FindPredicateEntryByPredicateEntry(const PredicateEntry& pe) {
    if (!ISPredicateEntryDup(pe)) {
        throw ProgramException("Find Predicate Entry in Symbol Table failed", ProgramException::kFatalError);
    }  // The Predicate you're looking for is not in this symbol table, this should never happens.

    std::list<PredicateEntry>& p_entries = preds_map_[pe.name];
    for (PredicateEntry& p_entry : p_entries) {
        if (p_entry.EqualsTo(pe)) { return &p_entry; }
    }
    return nullptr;  // This control flow should never reach, but it makes compiler happy.
}

bool SymbolTable::ISPredicateEntryDup(const PredicateEntry& p) {
    if (!preds_map_.count(p.name)) { return false; } // no name inside the map.
    const std::list<PredicateEntry>& predicates = preds_map_[p.name];
    for (const PredicateEntry& predicate : predicates) {
        if (predicate.EqualsTo(p)) { return true; }
    }
    return false;
}

void SymbolTable::Print(std::ostream& os) const {
    os << "UnBound Label : " << std::endl;
    for (const UnBoundToken& unbound : unbounds_) {
        os << "[" << &unbound << "]" << Encode(unbound);
    }
    os << std::endl << "Bound Label : " << std::endl;
    for (const BoundToken& bound : bounds_) {
        os << "["<< &bound <<"]" << Encode(bound);
    }
    os << std::endl << "Constants Number : " << std::endl;
    for (const NumberToken& constant : constants_) {
        os << "[" << &constant << "]" << Encode(constant);
    }
    os << std::endl << "Predicate : " << std::endl;
    for (const PredicateEntry* entry_ptr : predicates_trace_) {
        os << *entry_ptr << std::endl;
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
    entry_buffer_pointer_->symbols.push_back(&FindIdentifierByToken(*node_ptr->symbol_ptr_));
}

void SymbolTable::OnVisit(NameNode* node_ptr) {
    entry_buffer_pointer_->name = static_cast<std::string>(*(node_ptr->label_ptr_));
}