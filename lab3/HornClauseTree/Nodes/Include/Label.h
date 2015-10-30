#ifndef LABEL_H
#define LABEL_H
#include "token.h"

//
// struct Label
// Derived struct of Token struct, classifies token as a Label
//name node in the abstract semantic tree of horn clauses, EBNF grammar :
//	name->LABEL
//
struct Label : Token{
	Label(){}

	Label(std::string& s);
	//
	//accept()
	//A virtual function overrided from Token class, accept visitor to do visitor routines.
	//
	virtual void accept(Visitor &v) override;
};

#endif