#ifndef PREDICATE_H
#define PREDICATE_H

#include "token.h"
#include "Symbol.h"
#include "Label.h"
#include "PredicateST.h"
#include <iostream>

//
// struct Predicate
// Part of Token tree, stores name(Label) and Symbol Token as its children
//
struct Predicate : Token {
	Predicate();
	//
	//has_symbol()
	//return a boolean value that indicates whether the predicate has a symbol.
	bool has_symbol() const;

	std::shared_ptr<Label> get_name();

	std::shared_ptr<Symbol> get_symbol();

	std::shared_ptr<PredicateST> make_predicate_st();
	//
	//accept()
	//A virtual function overrided from Token class, accept visitor to do visitor routines.
	//
	virtual void accept(Visitor &v) override;
};

#endif