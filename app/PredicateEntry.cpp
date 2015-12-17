// PredicateEntry.cpp -- This file defines PredicateEntry class which stores inside the Symbol Table.
// Created by Yu Xiao, Anqi Zhang, all right reserved.
//
#include "stdafx.h"
#include "PredicateEntry.h"
#include "Utils.h"
#include "HornclauseTokens.h"
#include <sstream>

PredicateEntry::PredicateEntry() {}

PredicateEntry::PredicateEntry(const std::string& name_) : name(name_) {}

PredicateEntry::PredicateEntry(const LabelToken& name_) : name(name_) {}

bool PredicateEntry::EqualsTo(const PredicateEntry& that) const{
    if (name != that.name)                     { return false; }
    if (symbols.size() != that.symbols.size()) { return false; }

    std::vector<const BaseToken*>::const_iterator this_it = symbols.begin();
    std::vector<const BaseToken*>::const_iterator that_it = that.symbols.begin();

    for (; this_it != symbols.end(); ++this_it, ++that_it) {
        if (**this_it != **that_it) { return false; }  // looks nice, right?
    }

    return true;
}

PredicateEntry::operator const std::basic_string<char>() const {
    std::ostringstream oss;
    oss << Encode("(") << Encode(name); // Print Address for testing.
    for (const BaseToken* symbol_ptr : symbols) {
        if (symbol_ptr->type == BaseToken::BOUND) oss << Encode(*dynamic_cast<const BoundToken*>(symbol_ptr));
        else                                      oss << Encode(*symbol_ptr);
    }
    oss << Encode(")");
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const PredicateEntry& p) {
    os << static_cast<const std::string>(p);
    return os;
}