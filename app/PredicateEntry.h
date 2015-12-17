// PredicateEntry.h -- This file declares PredicateEntry class which stores inside the Symbol Table.
// Created by Yu Xiao, Anqi Zhang, all right reserved.
//
#ifndef PREDICATE_ENTRY_H
#define PREDICATE_ENTRY_H
#include <iostream>
#include <vector>
#include "HornclauseTokens.h"

// Stores the name of predicate and references to the symbols inside SymbolTable singleton.
struct PredicateEntry {
    // Stores the name of predicate.
    std::string name;

    // Stores symbol pointers referenced to SymbolTable singleton.
    std::vector<const BaseToken*> symbols;

    // Creates a default Predicate entry with empty name string.
    PredicateEntry();
    
    // Passes in a name of predicates, but empty symbols.
    PredicateEntry(const std::string& name_);

    // Paases in a LabelToken containing the name, but empty symbols.
    PredicateEntry(const LabelToken& name_);

    // Returns true if name, all symbols in PredicateEntries are the same.
    bool EqualsTo(const PredicateEntry&) const;

    // Returns string representing this predicate.
    operator const std::string() const;

    // Print this predicate string to {ostream}. 
    friend std::ostream& operator<<(std::ostream& os, const PredicateEntry& p);
};

#endif
