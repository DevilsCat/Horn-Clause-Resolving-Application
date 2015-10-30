#include "stdafx.h"
#include "Predicate.h"
#include "Visitor.h"

#define NAME_POS	0
#define SYMBOL_POS	1
#define SIZE_WITH_SYMBOL 2

Predicate::Predicate() :
	Token(PREDICATE)
{}

void Predicate::accept(Visitor& v){
	v.visit(this);
	std::dynamic_pointer_cast<Label> (get_name())->accept(v);
	if (has_symbol()){
		std::dynamic_pointer_cast<Symbol> (get_symbol())->accept(v);
	}
}

bool Predicate::has_symbol() const {
	return children.size() == SIZE_WITH_SYMBOL;
}

std::shared_ptr<Label> Predicate::get_name() {
	return std::dynamic_pointer_cast<Label>(children[NAME_POS]);
}

std::shared_ptr<Symbol> Predicate::get_symbol() {
	return std::dynamic_pointer_cast<Symbol>(children[SYMBOL_POS]);
}

std::shared_ptr<PredicateST> Predicate::make_predicate_st() {
	// init and get the name.
	std::shared_ptr<PredicateST> pred_st = std::make_shared<PredicateST>(get_name());

	// clone the symbols.
	pred_st->clone_symbols(get_symbol()->children);

	return pred_st;
}