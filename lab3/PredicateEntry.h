#ifndef PREDICATE_ENTRY_H
#define PREDICATE_ENTRY_H
#include <iostream>
#include <vector>
#include "HornclauseTokens.h"

struct PredicateEntry {
    std::string name;
    std::vector<const BaseToken*> symbols;
    PredicateEntry();
    PredicateEntry(const std::string& name_);
    PredicateEntry(const LabelToken& name_);
    bool EqualsTo(const PredicateEntry&) const;

    operator const std::string() const;
    friend std::ostream& operator<<(std::ostream& os, const PredicateEntry& p);
};

#endif
