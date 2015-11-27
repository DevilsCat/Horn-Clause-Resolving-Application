// HornclauseDatabase.cpp -- This file defines a HornclauseDatabase and Entry classes
// used to store, retrieve display horn clauses.
// Created by Anqi Zhang, Yu Xiao, all right reserved.
//
#include "stdafx.h"
#include "HornclauseDatabase.h"
#include "HornclauseASTNodes.h"
#include "Utils.h"
#include <algorithm>
#include "ProgramException.h"
#include <sstream>
#include "OutputHandler.h"

// Initializes class singleton.
std::shared_ptr<HornclauseDatabase> HornclauseDatabase::deductive_database_ = nullptr;

std::shared_ptr<HornclauseDatabase> HornclauseDatabase::instance() {
    if (deductive_database_ == nullptr)
        throw ProgramException("HornclauseDatabase not initialized.", 
                                ProgramException::kFatalError);
    return deductive_database_;
}

void HornclauseDatabase::init(SymbolTable& symbol_table) {
    if (deductive_database_ == nullptr)
        deductive_database_ = std::shared_ptr<HornclauseDatabase>(new HornclauseDatabase(symbol_table));
}

HornclauseDatabase::HornclauseDatabase(SymbolTable& symbol_table) :
    symbol_table_(symbol_table), new_hornclause_(nullptr)
{}

void HornclauseDatabase::FillHornclauseFromTree(std::shared_ptr<RootNode> root) {
    root->Accept(*this);  // Apply Visitor pattern.
}

void HornclauseDatabase::AddHornclauseEntry(Entry& entry) {
    if (IsHornclauseEntryDup_(entry)) { return; }

    // Update: Before add hornclause into this database, populate all PredicateEntry to symbol table first.
    for (std::shared_ptr<PredicateEntry>& pe : entry.head) {
        if (!symbol_table_.ISPredicateEntryDup(*pe))  // Warning: To prevent Bugs when try to reproduce indetical pointer.
            pe = std::shared_ptr<PredicateEntry>(&symbol_table_.InsertPredicate(*pe));
    }
    for (std::shared_ptr<PredicateEntry>& pe : entry.body) {
        if (!symbol_table_.ISPredicateEntryDup(*pe))
            pe = std::shared_ptr<PredicateEntry>(&symbol_table_.InsertPredicate(*pe));
    }

    hornclause_entries_.push_back(entry);
}

bool HornclauseDatabase::RetrieveHornclauseEntry(Entry& result, const unsigned& idx) {
    if (idx >= size()) { return false; }
    result = hornclause_entries_[idx];
    return true;
}

void HornclauseDatabase::OnPreVisit(HornclauseNode*) {
    new_hornclause_ = new Entry();
}

void HornclauseDatabase::OnPostVisit(HornclauseNode*) {
    AddHornclauseEntry(*new_hornclause_);
    delete new_hornclause_;
}

void HornclauseDatabase::OnPreVisit(HeadNode*) {
    predicate_buffer_.clear();
}

void HornclauseDatabase::OnPostVisit(HeadNode*) {
    new_hornclause_->head = predicate_buffer_;
}

void HornclauseDatabase::OnPreVisit(BodyNode*) {
    predicate_buffer_.clear();
}

void HornclauseDatabase::OnPostVisit(BodyNode*) {
    new_hornclause_->body = predicate_buffer_;
}

void HornclauseDatabase::OnVisit(PredicateNode* node) {
    predicate_buffer_.push_back(  // The predicate to push back should come from symbol table.
        std::shared_ptr<PredicateEntry>(symbol_table_.FindPredicateEntryByNode(*node)));
}

bool HornclauseDatabase::IsHornclauseEntryDup_(const Entry& me) const {
    return std::find_if(hornclause_entries_.begin(), hornclause_entries_.end(), 
            [&me](const Entry& other) -> bool {
        return me.EqualsTo(other);  // Uses encapsulated determine method inside {Entry}.
    }) != hornclause_entries_.end();
}

int HornclauseDatabase::Display(const unsigned& offset, const unsigned& num_entries) const {
    size_t upper_bound = std::min(offset + num_entries, size());
    for (size_t i = offset; i < upper_bound; ++i) {
        std::ostringstream oss;
        oss << i + 1 << Encode(":") << hornclause_entries_[i];
        *OutputHandler::instance() << oss.str() << std::endl;
    }
	return upper_bound - offset;  // Returns the number of lines that in fact prints out.
}

size_t HornclauseDatabase::size() const {
    return hornclause_entries_.size();
}

HornclauseDatabase::Entry& HornclauseDatabase::Entry::operator=(const Entry& other) {
    head.clear();
    body.clear();
    for (std::shared_ptr<PredicateEntry> head_entry : other.head) {
        std::shared_ptr<PredicateEntry> new_entry = std::make_shared<PredicateEntry>(head_entry->name);
        for (const BaseToken* token : head_entry->symbols) {
            new_entry->symbols.push_back(token);
        }
        head.push_back(new_entry);
    }
    for (std::shared_ptr<PredicateEntry> body_entry : other.body) {
        std::shared_ptr<PredicateEntry> new_entry = std::make_shared<PredicateEntry>(body_entry->name);
        for (const BaseToken* token : body_entry->symbols) {
            new_entry->symbols.push_back(token);
        }
        body.push_back(new_entry);
    }
    return *this;
}

bool HornclauseDatabase::Entry::IsFact() const {
    return !head.empty() && body.empty();
}

HornclauseDatabase::Entry::PredicateEntryIterator HornclauseDatabase::Entry::EraseBodyAt(const unsigned& idx) {
    PredicateEntryIterator it = body.begin();
    return body.erase(it + idx);
}

void HornclauseDatabase::Entry::InsertBodyAt(const unsigned& idx, PredicateEntryIterator first, PredicateEntryIterator last) {
    PredicateEntryIterator it = EraseBodyAt(idx);
    body.insert(it, first, last);
}

bool HornclauseDatabase::Entry::EqualsTo(const Entry& other) const {
    if (head.size() != other.head.size() || body.size() != other.body.size()) { return false; }

    // Create a PredicateEntry labda, though I really want to compare the address, but somehow insert predicate is buggy.
    auto PredicateEntryComparator = [](std::shared_ptr<PredicateEntry> lhs, std::shared_ptr<PredicateEntry> rhs)->bool {
        return lhs->EqualsTo(*rhs);
    };
    return equal(head.begin(), head.end(), other.head.begin(), PredicateEntryComparator) &&
           equal(body.begin(), body.end(), other.body.begin(), PredicateEntryComparator);
}

std::ostream& operator<<(std::ostream& os, const HornclauseDatabase::Entry& entry) {
    os << Encode("(");
    if (entry.head.size() == 1)  // single predicate head
        os << *entry.head.front();
    else {                       // multiple predicates head
        os << Encode("(");
        std::for_each(entry.head.begin(), entry.head.end(), [&os](std::shared_ptr<PredicateEntry> p){ os << *p; });
        os << Encode(")");
    }
    if (!entry.body.empty()) {
        os << Encode("(");
        for (std::shared_ptr<PredicateEntry> predicate_ptr : entry.body)
            os << *predicate_ptr;
        os << Encode(")");
    }
    os << ")";
    return os;
}