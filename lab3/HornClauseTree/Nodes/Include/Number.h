#ifndef NUMBER_H
#define NUMBER_H
#include "token.h"
#include <sstream>

//
// struct Number
// Derived struct of Token struct, classifies token as a integer, and interpret stores the real uint value
// 
struct Number : Token{
	unsigned int number;

	Number(std::string& s);
	//
	//accept()
	//A virtual function overrided from Token class, accept visitor to do visitor routines.
	//
	virtual void accept(Visitor &v) override;
};

#endif