// unifier.h -- Declares a unifier class to performs unification on a symbol table.
// Created by Anqi Zhang, Yu Xiao.
//
#ifndef UNIFIER_H
#define UNIFIER_H
#include "SymbolTable.h"
#include "HornclauseDatabase.h"

// This class takes a referernce of SymbolTable, and performs unification.
// Sample Usages:
//   Unifier unifier(*SymboleTable::instance());
//   unifier.UnifyHornclauses(entries, first_entry, second_entry);
class Unifier {
public:
    // Takes a reference of {SymbolTable} to initialize.
    Unifier(SymbolTable& symbol_table);

    // Copies fist and second entires, unifies first copy with second, stores result in 
    // vector of entries and return numbers of unified horn clauses. 
    size_t UnifyHornclauses(std::vector<HornclauseDatabase::Entry>&, 
                            const HornclauseDatabase::Entry&, const HornclauseDatabase::Entry&);

private:
    // Unifies two entries, returns true if they can be unified. If unification success, the two
    // entries will be the same.
    bool Unify(PredicateEntry*&, PredicateEntry*&);

    // Applies the subsititutions resulted from two {PredicateEntry} to a horn clause.
    void ApplyAllSubstitutionsToHornclause(HornclauseDatabase::Entry&);

    // Returns true if first token can perfom substituion with second token and stores the subsitution order into pair.
    static bool CanPerformSubstitution(std::pair<const BaseToken*, const BaseToken*>&, const BaseToken*, const BaseToken*);

    // Substitutes the head or body of {PredicateEntry} according to pair.
    static bool SubstituteTokensInPredicateEntry(std::vector<const BaseToken*>&, std::pair<const BaseToken*, const BaseToken*>& pair);

    // Substitutes the dst token by src token.
    static void SubstituteToken(const BaseToken** dst, const BaseToken** src);

    // A container to records the substitution of one subsitution action. 
    std::vector<std::pair<const BaseToken*, const BaseToken*>> token_substitutions_;

    // Working copy of current copy.
    HornclauseDatabase::Entry first_hornclause_copy_;

    // Working copy of following copy (apprears behind current copy).
    HornclauseDatabase::Entry second_hornclause_copy_;

    // Stores the reference of {SymbolTable} singleton.
    SymbolTable& symbol_table_;
};

#endif
