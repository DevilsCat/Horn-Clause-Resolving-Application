#ifndef NUMBER_TOKEN_H
#define NUMBER_TOKEN_H
#include "BaseToken.h"

//
// struct Number
// Derived struct of Token struct, classifies token as a integer, and interpret stores the real uint value
// 
struct NumberToken : BaseToken{
	unsigned number;

    explicit  NumberToken(std::string& s);

};

#endif