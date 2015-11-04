#include "stdafx.h"
#include "DeductiveDatabase.h"
#include "RootNode.h"
#include "HeadNode.h"
#include "BodyNode.h"
#include "PredicateNode.h"
#include "Utils.h"
#include <algorithm>

DeductiveDatabase::DeductiveDatabase(SymbolTable& symbol_table) :
    symbol_table_(symbol_table), hornclause_buffer_ptr_(nullptr)
{}

void DeductiveDatabase::FillHornclauseFromTree(std::shared_ptr<RootNode> root) {
    root->Accept(*this);
}

void DeductiveDatabase::AddHornclauseEntry(HornclauseDatabaseEntry& entry) {
    if (IsHornclauseEntryDup(entry)) { return; }

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

bool DeductiveDatabase::RetrieveHornclauseEntry(HornclauseDatabaseEntry& result, const unsigned& idx) {
    if (idx >= size()) { return false; }
    result = hornclause_entries_[idx];
    return true;
}

void DeductiveDatabase::OnPreVisit(HornclauseNode*) {
    hornclause_buffer_ptr_ = new HornclauseDatabaseEntry();
}

void DeductiveDatabase::OnPostVisit(HornclauseNode*) {
    AddHornclauseEntry(*hornclause_buffer_ptr_);
}

void DeductiveDatabase::OnPreVisit(HeadNode*) {
    predicate_buffer_.clear();
}

void DeductiveDatabase::OnPostVisit(HeadNode*) {
    hornclause_buffer_ptr_->head = predicate_buffer_;
}

void DeductiveDatabase::OnPreVisit(BodyNode*) {
    predicate_buffer_.clear();
}

void DeductiveDatabase::OnPostVisit(BodyNode*) {
    hornclause_buffer_ptr_->body = predicate_buffer_;
}

void DeductiveDatabase::OnVisit(PredicateNode* node) {
    predicate_buffer_.push_back(std::shared_ptr<PredicateEntry>(symbol_table_.FindPredicateEntryByNode(*node)));
}

bool DeductiveDatabase::IsHornclauseEntryDup(const HornclauseDatabaseEntry& me) const {
    return std::find_if(hornclause_entries_.begin(), hornclause_entries_.end(), 
            [&me](const HornclauseDatabaseEntry& other) -> bool {
        return me.EqualsTo(other);
    }) != hornclause_entries_.end();
}

int DeductiveDatabase::Display(std::ostream& os, const unsigned& offset, const unsigned& num_entries) const {
    size_t upper_bound = std::min(offset + num_entries, size());
	for (size_t i = offset; i < upper_bound; ++i)
		os << i + 1 << Encode(":") << hornclause_entries_[i] << std::endl;
	return upper_bound - offset;  // Returns the number of lines that in fact prints out.
}

size_t DeductiveDatabase::size() const {
    return hornclause_entries_.size();
}

void HornclauseDatabaseEntry::operator=(const HornclauseDatabaseEntry& other) {
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
}

bool HornclauseDatabaseEntry::IsFact() const {
    return !head.empty() && body.empty();
}

HornclauseDatabaseEntry::PredicateEntryIterator HornclauseDatabaseEntry::EraseBodyAt(const unsigned& idx) {
    PredicateEntryIterator it = body.begin();
    return body.erase(it + idx);

}

void HornclauseDatabaseEntry::InsertBodyAt(const unsigned& idx, PredicateEntryIterator first, PredicateEntryIterator last) {
    PredicateEntryIterator it = EraseBodyAt(idx);
    body.insert(it, first, last);
}

bool HornclauseDatabaseEntry::EqualsTo(const HornclauseDatabaseEntry& other) const {
    if (head.size() != other.head.size() || body.size() != other.body.size()) { return false; }

    // Create a PredicateEntry labda, though I really want to compare the address, but somehow insert predicate is buggy.
    auto PredicateEntryComparator = [](std::shared_ptr<PredicateEntry> lhs, std::shared_ptr<PredicateEntry> rhs)->bool {
        return lhs->EqualsTo(*rhs);
    };
    return equal(head.begin(), head.end(), other.head.begin(), PredicateEntryComparator) &&
           equal(body.begin(), body.end(), other.body.begin(), PredicateEntryComparator);
}

std::ostream& operator<<(std::ostream& os, const HornclauseDatabaseEntry& entry) {
    os << Encode("(") << *entry.head[0];
    if (!entry.body.empty()) {
        os << Encode("(");
        for (std::shared_ptr<PredicateEntry> predicate_ptr : entry.body)
            os << *predicate_ptr;
        os << Encode(")");
    }
    os << ")";
    return os;
}