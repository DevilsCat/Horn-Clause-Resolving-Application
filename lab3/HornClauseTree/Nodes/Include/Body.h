#ifndef BODY_H
#define BODY_H
#include "token.h"
#include "predicate.h"
#include <iostream>

//
// struct Symbol
// Part of Token tree, stores Predicate Token as its children
//
struct  Body : Token {
	Body();
	//
	//accept()
	//A virtual function overrided from Token class, accept visitor to do visitor routines.
	//
	virtual void accept(Visitor &v) override;
};

#endif