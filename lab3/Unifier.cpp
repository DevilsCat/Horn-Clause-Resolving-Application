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
    std::vector<HornclauseDatabase::Entry>& hornclause_entries,
        const HornclauseDatabase::Entry& first_hornclause,
        const HornclauseDatabase::Entry& second_hornclause) {
    // Updated to extra credits.
    for (size_t i = 0; i < first_hornclause.head.size(); ++i) {
        for (size_t j = 0; j < second_hornclause.body.size(); ++j) {
            first_hornclause_copy_ = first_hornclause;
            second_hornclause_copy_ = second_hornclause;
            PredicateEntry* head_pe = first_hornclause_copy_.head[i].get();
            PredicateEntry* body_pe = second_hornclause_copy_.body[j].get();
            if (Unify(head_pe, body_pe)) {                   // Once Unification succeeds, the head and body predicates
                if (first_hornclause_copy_.IsFact())         // unify to the same. We need to remove "j" position body  
                    second_hornclause_copy_.EraseBodyAt(j);  // if first hornclause is a fact.
                else
                    second_hornclause_copy_.InsertBodyAt(    // Otherwise, subustitude it.
                        j,
                        first_hornclause_copy_.body.begin(),
                        first_hornclause_copy_.body.end());
                ApplyAllSubstitutionsToHornclause(second_hornclause_copy_);
                hornclause_entries.push_back(second_hornclause_copy_);
            }
            token_substitutions_.clear();
        }
    }
    return hornclause_entries.size();
}

void Unifier::ApplyAllSubstitutionsToHornclause(HornclauseDatabase::Entry& hornclause) {
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
    for (; head_token_ptr_it != head_pe->symbols.end(); ++head_token_ptr_it, ++body_token_ptr_it) {
        const BaseToken* head_token_ptr = *head_token_ptr_it;
        const BaseToken* body_token_ptr = *body_token_ptr_it;
        std::pair<const BaseToken*, const BaseToken*> substitute_pair;
        if (CanPerformSubstitution(substitute_pair, head_token_ptr, body_token_ptr)) {
            SubstituteTokensInPredicateEntry(head_pe->symbols, substitute_pair);
            SubstituteTokensInPredicateEntry(body_pe->symbols, substitute_pair);
            token_substitutions_.push_back(substitute_pair);
        } else {
            return false;
        }
    }
    return true;
}

bool Unifier::CanPerformSubstitution(
        std::pair<const BaseToken*, const BaseToken*>& result, 
        const BaseToken* head_token, 
        const BaseToken* body_token) {
    
    // The pointer to tokens are they same.
    if (*head_token == *body_token) { return true; }  // Since they're already unified. 
    // Two Tokens are Different constants.
    if (*head_token == BaseToken::NUMBER && *body_token== BaseToken::NUMBER) { return false; }
    // Two Tokens are both Bound
    if (*head_token == BaseToken::BOUND && *body_token == BaseToken::BOUND) { return false; }
    // One is Constant another is Bound, but with different value.
    if (*head_token == BaseToken::NUMBER && *body_token == BaseToken::BOUND) {
        if (dynamic_cast<const BoundToken*>(body_token)->value != dynamic_cast<const NumberToken*>(head_token)->number)
            return false;
    }
    if (*head_token == BaseToken::BOUND && *body_token == BaseToken::NUMBER) {
        if (dynamic_cast<const BoundToken*>(head_token)->value != dynamic_cast<const NumberToken*>(body_token)->number)
            return false;
    }
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

