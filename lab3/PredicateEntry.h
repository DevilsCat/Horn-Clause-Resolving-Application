#ifndef PREDICATE_ENTRY_H
#define PREDICATE_ENTRY_H
#include <iostream>
#include "BaseToken.h"
#include "LabelToken.h"

struct PredicateEntry {
    std::string name;
    std::vector<const BaseToken*> symbols;
    PredicateEntry();
    PredicateEntry(const LabelToken& name_);
    bool EqualsTo(const PredicateEntry&) const;

    friend std::ostream& operator<<(std::ostream& os, const PredicateEntry& p);
};

#endif
