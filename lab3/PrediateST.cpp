// predicate_st.h -- Defines a predicate class used in symbol table
// Created by Anqi Zhang, Yu Xiao
//
#include "stdafx.h"
#include "PredicateST.h"
#include <iostream>
#include <string>

PredicateST::PredicateST(std::shared_ptr<NameNode>& n) : 
	name(n->label) 
{}

PredicateST::~PredicateST() {}

void PredicateST::clone_symbols(std::vector<std::shared_ptr<Token>>& other_symbols) {
	std::vector<std::shared_ptr<Token>>::iterator it = other_symbols.begin();
	for (; it != other_symbols.end(); ++it) { // perform a shallow clone.
		symbols.push_back((it->get()));
	}
}

std::ostream& operator<<(std::ostream& os, PredicateST const& p) {
	os << p.name.label << " ";
	for (Token* symbol_ptr : p.symbols) {
		os << static_cast<const std::string>(*symbol_ptr) << " ";
	}
	return os;
}