#include "stdafx.h"
#include "PredicateEntry.h"
#include "Utils.h"
#include "BoundToken.h"
#include <ctype.h>

/////////////////// Here is For PredicateEntry. /////////////////////////

PredicateEntry::PredicateEntry() {}

PredicateEntry::PredicateEntry(const std::string& name_) : name(name_) {}

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
    os <<Encode("(") << Encode(p.name); // Print Address for testing.
    for (const BaseToken* symbol_ptr : p.symbols) {
        if (symbol_ptr->type == BaseToken::BOUND) os << Encode(*dynamic_cast<const BoundToken*>(symbol_ptr));
        else                                      os << Encode(*symbol_ptr);
    }
    os << Encode(")");
    return os;
}