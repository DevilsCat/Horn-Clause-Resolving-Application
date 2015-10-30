#ifndef SYMBOL_H
#define SYMBOL_H
#include "token.h"
#include <functional>
#include <algorithm>

//
// struct Symbol
// Part of Token tree, stores Number/Label Token as its children
//
struct Symbol : Token{
	Symbol();
	//
	//accept()
	//A virtual function overrided from Token class, accept visitor to do visitor routines.
	//
	virtual void accept(Visitor &v) override;
};

#endif