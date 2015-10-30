// unifier.h -- Declares a unifier class to performs unification on a symbol table.
// Created by Anqi Zhang, Yu Xiao.
//
#ifndef UNIFIER_H
#define UNIFIER_H
#include "SymbolTable.h"

//
// class Unifier
// This class takes a **reference**(we always want symbol table to be unique) of symbol table,
// and performs unification.
// Sample Usages:
//   ...
//   /* ...some how you have a filled SymbolTable object st */
//   SymbolTable st;
//   ...
//   Unifier unifier(st);
//   unifier.unify_all();
//
class Unifier {
private:
	// A reference of Symbol Table.
	SymbolTable& st_;

    

	// A container to records the substitution of one subsitution action. 
	std::vector<std::pair<Token, Token>> subs_v_;
	
	// Working copy of current copy.
	std::shared_ptr<PredicateST> cur_copy_;
	
	// Working copy of following copy (apprears behind current copy).
	std::shared_ptr<PredicateST> fol_copy_;

public:
	//
	// Constructor
	// Takes a reference of SymbolTable and stores in member variable.
	//
	Unifier(SymbolTable&);

	//
	// unify_all()
	// Performs unifications on the whole symbol table.
	//
	void unify_all();

private:

	//
	// unify()
	// Perform unification on two Predicates (PredicateST).
	//
	void unify(const PredicateST &, const PredicateST &);

	//
	// compare_sub()
	// Takes two the pointer of Token poiner, compares two token and performs
	// substituion following unification rule.
	// RULEs:
	//  (1) if same variable, return;
	//  (2) if differet constants, discard (throw runtime error);
	//  (3) if both labels, substitute follower by current;
	//  (4) if one label one number, substitute label by number.
	//
	void compare_sub(Token**, Token**);

	//
	// substitute()
	// Substitutes first Token by second Token.
	//
	void substitute(Token**, Token**);

	//
	// substitute()
	// Substitutes Tokens in vector which match first Token by second Token. Returns
    // true if any substition happens.
	//
	bool substitute(std::vector<Token*> &, Token*, Token*);

	//
	// print_result()
	// Once a unification finished, you can print a formatted result.
	//
	void print_result(PredicateST const &cur, PredicateST const &fol);

};

#endif
