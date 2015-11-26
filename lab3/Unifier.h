// unifier.h -- Declares a unifier class to performs unification on a symbol table.
// Created by Anqi Zhang, Yu Xiao.
//
#ifndef UNIFIER_H
#define UNIFIER_H
#include "SymbolTable.h"
#include "HornclauseDatabase.h"

//
// class Unifier
// This class takes a **reference**(we always want symbol table to be unique) of symbol table,
// and performs unification.
// Sample Usages:
//   ...
//   /* ...some how you have a filled SymbolTable object st */
//   SymbolTable st;
//   ...
//   Unifier unifier(st);
//   unifier.unify_all();
//
class Unifier {
public:
    Unifier(SymbolTable& symbol_table);

    size_t UnifyHornclauses(std::vector<HornclauseDatabase::Entry>&, const HornclauseDatabase::Entry&, const HornclauseDatabase::Entry&);

private:
    bool Unify(PredicateEntry*&, PredicateEntry*&);

    void ApplyAllSubstitutionsToHornclause(HornclauseDatabase::Entry&);

    bool CanPerformSubstitution(std::pair<const BaseToken*, const BaseToken*>&, const BaseToken*, const BaseToken*);

    bool SubstituteTokensInPredicateEntry(std::vector<const BaseToken*>&, std::pair<const BaseToken*, const BaseToken*>& pair);

    void SubstituteToken(const BaseToken** dst, const BaseToken** src);

    SymbolTable& symbol_table_;

    // A container to records the substitution of one subsitution action. 
    std::vector<std::pair<const BaseToken*, const BaseToken*>> token_substitutions_;

    // Working copy of current copy.
    HornclauseDatabase::Entry first_hornclause_copy_;

    // Working copy of following copy (apprears behind current copy).
    HornclauseDatabase::Entry second_hornclause_copy_;
};

#endif
