#ifndef LABEL_TOKEN_H
#define LABEL_TOKEN_H
#include "BaseToken.h"

//
// struct Label
// Derived struct of Token struct, classifies token as a Label
//name node in the abstract semantic tree of horn clauses, EBNF grammar :
//	name->LABEL
//
struct LabelToken : BaseToken{
    explicit LabelToken(const std::string& s);

    explicit LabelToken(const TokenType& type, const std::string& s);
};

#endif