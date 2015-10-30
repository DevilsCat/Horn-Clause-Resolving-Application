#ifndef HORNCLAUSE_H
#define HORNCLAUSE_H
#include "token.h"
#include "Head.h"
#include "Body.h"
#include <iostream>

//
// struct Symbol
// Part of Token tree, stores Head and Body Token as its children
//
struct  Hornclause : Token {
	Hornclause();
	//
	//hasBody()
	//return a boolean value that indicates whether the horn clause has a body.
	//
	bool hasBody();
	//
	//accept()
	//A virtual function overrided from Token class, accept visitor to do visitor routines.
	//
	virtual void accept(Visitor &v) override;
};

#endif