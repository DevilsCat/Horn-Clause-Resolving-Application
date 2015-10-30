// symbol_table.h -- Implements a Symbol Table class that stores variables, constants and predicates showing up
// in the input file.
// Created by Yu Xiao, Anqi Zhang
//
#include "stdafx.h"
#include "SymbolTable.h"
#include "Predicate.h"
#include <iostream>
#include <algorithm>

SymbolTable::SymbolTable() {}

SymbolTable::~SymbolTable() {}

void SymbolTable::fill(std::shared_ptr<Token> const& root) {
	root->accept(*this);
}

void SymbolTable::start_map_iteration() {
	map_it_ = preds_map_.begin();
}

bool SymbolTable::map_has_next() {
	return map_it_ != preds_map_.end();
}

std::vector<PredicateST>& SymbolTable::map_next() {
	std::vector<PredicateST>& v = map_it_->second;
	++map_it_;
	return v;
}

void SymbolTable::insert_symbol(Token* t) {
	if (*t != (Token::NUMBER | Token::LABEL)) { return; } // error check

	if (*t == Token::NUMBER) {
		Number constant = *dynamic_cast<Number *>(t);
		insert_constant(constant);
	} else if (*t == Token::LABEL) {
		Label variable = *dynamic_cast<Label *>(t);
		insert_variable(variable);
	}
}

void SymbolTable::insert_variable(Label &v) {
	variables_.insert(v);
}

void SymbolTable::insert_constant(Number &n) {
	constants_.insert(n);
}

void SymbolTable::insert_predicate(PredicateST &p) {
	if (is_pred_dup(p)) { // check not duplicate
        std::cout << "Skipped duplicate predicate : " << p << std::endl;
	    return;
	} 

	// populate variables and constants
	insert_variable(p.name); // insert name

	for (Token* symbol_ptr : p.symbols) { // insert symbols
		insert_symbol(symbol_ptr);
	}

	// populate that predicate
	std::string label = p.name;
	if (!preds_map_.count(label)) { // key not exist
		preds_map_[label] = std::vector<PredicateST>();
	}

	for (Token* &sym_ptr : p.symbols) { // find unique symbol in symbol table
		sym_ptr = find_identity(*sym_ptr);
	}

	preds_map_[label].push_back(p);
}

// uses find_if to reduce the manualy searching workload.
Token* SymbolTable::find_identity(Token &t) {
	Token* ptr;
	if (t == Token::NUMBER) { 
		ptr = const_cast<Number*>(&*find_if(constants_.begin(), constants_.end(), TokenFinder(t)));
	}
	else {
		ptr = const_cast<Label*>(&*find_if(variables_.begin(), variables_.end(), TokenFinder(t)));
	}
	return ptr;
}

bool SymbolTable::is_pred_dup(const PredicateST &p) {
	// get predicates
	const std::string name = p.name.label;
	if (!preds_map_.count(name)) { return false; } // no key, thus no duplicate.
	const std::vector<PredicateST> preds = preds_map_[name];
	return preds.end() != std::find_if(preds.begin(), preds.end(), PredicateFinder(p));
}

void SymbolTable::visit(Predicate *node) {
	std::shared_ptr<PredicateST> pred_st = node->make_predicate_st();
	insert_predicate(*pred_st);
}

void SymbolTable::print() {
	for (auto p : preds_map_) {
		std::vector<PredicateST> preds = p.second;
		for (PredicateST pred : preds) {
			std::cout << pred << std::endl;
		}
	}
}

SymbolTable::TokenFinder::TokenFinder(const Token& t): 
	t_(t) 
{}

bool SymbolTable::TokenFinder::operator()(const Token& t) { 
	return t.label == t_.label; 
}

SymbolTable::PredicateFinder::PredicateFinder(const PredicateST& p) : 
	p_(p) 
{}

bool SymbolTable::PredicateFinder::operator()(const PredicateST& p) {
	if		(p_.name != p.name)						{ return false; }
	if (p_.symbols.size() != p.symbols.size())		{ return false; }

	std::vector<Token*>::const_iterator it = p.symbols.begin();
	std::vector<Token*>::const_iterator it_ = p_.symbols.begin();

	for (; it != p.symbols.end(); ++it, ++it_) {
		if (*(*it) != *(*it_)) { return false; } // hey, I know you will know this if you are patient enough!
	}
	return true;
}