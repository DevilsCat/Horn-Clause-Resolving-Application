// unifier.h -- Implements a unifier class to performs unification on a symbol table.
// Created by Anqi Zhang, Yu Xiao.
//
#include "stdafx.h"
#include <iostream>
#include "Unifier.h"

Unifier::Unifier(SymbolTable& symbol_table) :
    symbol_table_(symbol_table)
{}

size_t Unifier::UnifyHornclauses(
        std::vector<HornclauseDatabaseEntry>& hornclause_entries,
        const HornclauseDatabaseEntry& first_hornclause, 
        const HornclauseDatabaseEntry& second_hornclause) {

    for (size_t i = 0; i < second_hornclause.body.size(); ++i) {
        first_hornclause_copy_ = first_hornclause;
        second_hornclause_copy_ = second_hornclause;
        // For base requirement, head contains only one predicate
        PredicateEntry* head_pe = first_hornclause_copy_.head.front().get();
        PredicateEntry* body_pe = second_hornclause_copy_.body[i].get();
        if (Unify(head_pe, body_pe)) {                   // Once Unification succeeds, the predicates in "i" location 
            if (first_hornclause_copy_.IsFact()) {       // changed to unified one. But we need to remove it if first 
                second_hornclause_copy_.EraseBodyAt(i);  // hornclause is a fact.
            }
            ApplyAllSubstitutionsToHornclause(second_hornclause_copy_);
            hornclause_entries.push_back(second_hornclause_copy_);
        }
        token_substitutions_.clear();
    }
    return hornclause_entries.size();
}

void Unifier::ApplyAllSubstitutionsToHornclause(HornclauseDatabaseEntry& hornclause) {
    for (std::pair<const BaseToken*, const BaseToken*> token_token_pair : token_substitutions_) {
        // Substitute the head.
        for (std::shared_ptr<PredicateEntry> head_pe : hornclause.head) {
            SubstituteTokensInPredicateEntry(head_pe->symbols, token_token_pair);
        }
        // Substitute the body.
        for (std::shared_ptr<PredicateEntry> body_pe : hornclause.body) {
            SubstituteTokensInPredicateEntry(body_pe->symbols, token_token_pair);
        }
    }
}

bool Unifier::Unify(PredicateEntry*& head_pe, PredicateEntry*& body_pe) {
    if (head_pe->symbols.size() != body_pe->symbols.size()) { return false; }

    std::vector<const BaseToken*>::iterator head_token_ptr_it = head_pe->symbols.begin();
    std::vector<const BaseToken*>::iterator body_token_ptr_it = body_pe->symbols.begin();
    bool any_success = false;
    for (; head_token_ptr_it != head_pe->symbols.end(); ++head_token_ptr_it, ++body_token_ptr_it) {
        const BaseToken* head_token_ptr = *head_token_ptr_it;
        const BaseToken* body_token_ptr = *body_token_ptr_it;
        std::pair<const BaseToken*, const BaseToken*> substitute_pair;
        if (CanPerformSubstitution(substitute_pair, head_token_ptr, body_token_ptr)) {
            any_success |= SubstituteTokensInPredicateEntry(head_pe->symbols, substitute_pair);
            any_success |= SubstituteTokensInPredicateEntry(body_pe->symbols, substitute_pair);
            token_substitutions_.push_back(substitute_pair);
        }
    }
    return any_success;
}

bool Unifier::CanPerformSubstitution(
        std::pair<const BaseToken*, const BaseToken*>& result, 
        const BaseToken* head_token, 
        const BaseToken* body_token) {
    
    // The pointer to tokens are they same.
    if (*head_token == *body_token) { return false; } 
    // Two Tokens are Different constants.
    if (*head_token == BaseToken::NUMBER && *body_token== BaseToken::NUMBER) { return false; }
    // Two Tokens are both Bound
    if (*head_token == BaseToken::BOUND && *body_token == BaseToken::BOUND) { return false; }
    
    const BaseToken** src_token_ptr;
    const BaseToken** dst_token_ptr;

    // The rest case should contains a substitution.
    if (*head_token == BaseToken::NUMBER) {
        src_token_ptr = &head_token;
        dst_token_ptr = &body_token;
    } else if (*body_token == BaseToken::NUMBER) {
        src_token_ptr = &body_token;
        dst_token_ptr = &head_token;
    } else if (*head_token == BaseToken::BOUND) {
        src_token_ptr = &head_token;
        dst_token_ptr = &body_token;
    } else if (*body_token == BaseToken::BOUND) {
        src_token_ptr = &body_token;
        dst_token_ptr = &head_token;
    } else {
        src_token_ptr = &head_token;
        dst_token_ptr = &body_token;
    }
    
    result = std::make_pair(*src_token_ptr, *dst_token_ptr);
    return true;
}

bool Unifier::SubstituteTokensInPredicateEntry(
        std::vector<const BaseToken*>& dst_vector, 
        std::pair<const BaseToken*, const BaseToken*>& pair) {
    const BaseToken* substitute_for = pair.first;
    const BaseToken* compare_with = pair.second;
    bool is_success = false;
    for (const BaseToken*& target : dst_vector) {
        if (*target == *compare_with) {
            SubstituteToken(&target, &substitute_for);
            is_success = true;
        }
    }
    return is_success;
}

void Unifier::SubstituteToken(const BaseToken** dst, const BaseToken** src) {
    *dst = *src;
}

