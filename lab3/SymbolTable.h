// symbol_table.h -- Declares a Symbol Table class that stores variables, constants and predicates showing up
// in the input file.
// Created by Yu Xiao, Anqi Zhang
//
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <set>
#include <map>
#include <vector>
#include <memory>
#include "PredicateST.h"
#include "Visitor.h"
#include "TokenComparator.h"
#include "NumberToken.h"

//
// class SymbolTable
// Sample Usage:
//   SymbolTable st; // Create a symbol table
//   ...
//   std::shared_ptr<TokenRoot> tree; // Some how you will have a Token tree like this ... 
//   ...
//   st.fill(tree);
//   st.print();
//
class SymbolTable : Visitor {
	typedef std::map<std::string, std::vector<PredicateST>> MapType;
	
	// A distinct-element container to stores unique variables.
	std::set<LabelToken, TokenComparator> variables_;

	// A distinct-element container to stores unique constants.
	std::set<NumberToken, TokenComparator> constants_;

	// A chained-map container to store predicates (might have the same key)
	MapType preds_map_;

	// An iteraotr for this map, the accessing point to map container 
	// (via map_has_next() and map_next()).
	MapType::iterator map_it_;

public:
	//
	// Default constructor and deconstructor.
	//
	SymbolTable();

	~SymbolTable();

	// Semantically, Symbol Table should be unique. Thus does not allow
	// copy constructor and assignment operator.
	void operator= (SymbolTable&) = delete;
	SymbolTable(SymbolTable&) = delete;

	//
	// fill()
	// Fills The symbol table with Token tree.
	//
	void fill(std::shared_ptr<Token> const &root);
	
	// 
	// start_map_iteration()
	// Start iterating predicate map, be careful, this should be call
	// before calling map_has_next() and map_next()
	// Sample Usage:
	//   SymbolTable st;
	//   /* ...fill the symbol table... */
	//   st.start_map_iteration();
	//   while(st.map_has_next()) {
	//		std::vector<PredicateST> v = st.map_next();
	//      /* ...Now you can deal with the retrieved vector... */
	//   }
	//
	void start_map_iteration();

	//
	// map_has_next()
	// Returns true if map still have the next element. Usage see above.
	//
	bool map_has_next();

	//
	// map_next()
	// Returns the reference of vector in the map, and move to next vector.
	//
	std::vector<PredicateST>& map_next();

	virtual void OnVisit(Predicate *node) override;

	//
	// print() 
	// Traverse the symbol table and print a seprate line for each predicate by printing its name attribute followed
	// by the attributes of the symbols to which it points.
	//
	void print();

private:
	// 
	// struct TokenFinder
	// Uses to find the Token inside the vector
	//
	struct TokenFinder {
		//
		// Constructor
		// Takes a Token reference and stores it.
		//
		TokenFinder(const Token& t);

		//
		// operator()
		// Returns true if Token labels are the same.
		//
		bool operator()(const Token& t);

		// Variables to store the left hand Token.
		const Token t_;
	};

	//
	// struct PredicateFinder
	// This helper struct is used to find predicate in vector.
	//
	struct PredicateFinder {
		//
		// Constructor
		//
		PredicateFinder(const PredicateST& p);

		//
		// operator()
		// Returns true if and only if name and all Symbols are the same
		// in two PredicateST.
		//
		bool operator()(const PredicateST& p);

		// Stores left hand side PredicateST.
		PredicateST p_;
	};

	//
	// insert_symbol()
	// Inserts the symbol into the symbol table. Note that it should only
	// be either Token::Label or Token::Number, other cases will be ignored.
	//
	void insert_symbol(Token* t);

	//
	// insert_varaible()
	// Inserts the variable(Token::Label) into the symbol table(variables set).
	//
	void insert_variable(Label &v);
	
	//
	// insert_constant()
	// Inserts the const(Token::Number) into the symbol table(constants set).
	//
	void insert_constant(Number &n);

	//
	// insert_predicate()
	// Inserts PredicateST into the symbol table.
	//
	void insert_predicate(PredicateST &p);

	//
	// find_identity()
	// Returns pointer to the identity (Constant or Variable) inside local symbol table.
	//
	Token* find_identity(Token &);

	//
	// is_pred_dup()
	// Returns true if two predicates are duplicated, which is used to eliminate duplication.
	//
	bool is_pred_dup(const PredicateST &p);

};

#endif