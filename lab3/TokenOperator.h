// TokenComparator.h -- This file declares a TokenComparator struct used to compare between two Token.
// Created by Anqi Zhang, Yu Xiao
//
#ifndef TOKEN_OPERATOR_H
#define TOKEN_OPERATOR_H

#include "BaseToken.h"

//
// struct TokenComparator
// This Comparator specifies how Token object stores in STL container.
//
struct TokenComparator {
    bool operator()(const BaseToken& lhs, const BaseToken& rhs) const;
};

// 
// struct TokenFinder
// Uses to find the Token inside the vector
//
struct TokenFinder {
    //
    // Constructor
    // Takes a Token reference and stores it.
    //
    TokenFinder(const BaseToken& t);

    //
    // operator()
    // Returns true if Token labels are the same.
    //
    bool operator()(const BaseToken& t);

    // Variables to store the left hand Token.
    const BaseToken t_;
};

#endif

