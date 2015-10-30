// TokenRoot.h : Declares TokenRoot struct which program, which is the derived class to Token, and uses it to record semantic of root node of the horn clause tree. 
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef TOKENROOT_H
#define TOKENROOT_H
#include "token.h"
#include "Hornclause.h"

//
//struct TokenRoot
//a derived class of Token struct type that is the root node of abstract semantic tree of horn clauses.
//
struct TokenRoot : Token {
	//
	//accept()
	//A virtual function overrided from Token class, accept visitor to do visitor routines.
	//
	virtual void accept(Visitor &v) override;
};

#endif