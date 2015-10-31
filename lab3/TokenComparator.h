// TokenComparator.h -- This file declares a TokenComparator struct used to compare between two Token.
// Created by Anqi Zhang, Yu Xiao
//
#ifndef TOKEN_COMPARATOR_H
#define TOKEN_COMPARATOR_H

#include "BaseToken.h"

//
// struct TokenComparator
// This Comparator specifies how Token object stores in STL container.
//
struct TokenComparator {
    bool operator()(const BaseToken& lhs, const BaseToken& rhs) const;
};

#endif

