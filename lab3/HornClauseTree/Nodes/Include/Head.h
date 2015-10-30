#ifndef HEAD_H
#define HEAD_H
#include "token.h"
#include "Predicate.h"

//
// struct Head
// Part of Token tree, stores Predicate Token as its children
//
struct  Head : Token {
	Head();
	//
	//accept()
	//A virtual function overrided from Token class, accept visitor to do visitor routines.
	//
	virtual void accept(Visitor &v) override;
};

#endif