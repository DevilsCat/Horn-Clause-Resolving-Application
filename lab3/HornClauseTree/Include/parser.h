// parser.h : Declares a parser class performing parsing for one layer formatted output horn clause
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <memory>
#include "scanner.h"
#include "token.h"
#include "Hornclause.h"
#include "TokenRoot.h"

//
// class parser
// Pareses the input raw horn clauses (both well and bad formatted), and can perform semantic analysis.
// Sample Usage:
//   parser p(input_filename, output_filename);
//   int ret = p.parse();
//   // ... check ret and error code
//
class parser{
	// a re-defined type make determine Token type easier.
	typedef Token::token_t	Type;

	// Stores the input file name which uses to initiate an ifstream 
	std::string filename_;

	// An ifstream contains lines of content for extracting horn clause
	std::ifstream ifs_;

	// Scanner Object which uses to extract tokens from ifstream and store as a pointer
	scanner scanner_;

	// A Toke pointer stores the latest token pointer extracted from ifstream using Scanner object
	std::shared_ptr<Token> token_ptr;

	// A Hornclause struct object stores the temporary complete(partial complete hornclause).
	Hornclause buffer;

	// A Token Tree entering point.
	std::shared_ptr<TokenRoot> root;
public:

	//
	// Constructor
	// Takes a reference file name string used to open an input file stream.
	//
	parser(std::string& filename);

	//
	// parse()
	// Parses the input formatted horn clause, and stores in token tree abstraction representation
	// Usage examples:
	// Input:
	//   ( ( greater x y ) ( ( greater x z ) ) )
	// Token Tree:
	//  root
	//    |
	//  hornclause
	//	  | --head
	//	  |   `-- predicate
	//	  |     | -- x
	//	  |     | -- y
	//	  |     ` -- greater
	//	  `-- body
	//	     `-- predicate
	//	        | -- x
	//	        | -- z
	//	        ` -- greater
	//
	int parse();

	//
	// get_token_tree()
	// Get the token tree data structure this parser.
	// This method is for the after processing of input horn clauses.
	//
	std::shared_ptr<TokenRoot> get_token_tree();

	//
	// print_tree()
	// Print the Token tree for the sake of debugging. This method will
	// in fact recursively call print member method in each Token node.
	//
	void print_tree();

private:
	//
	// match()
	// Matches the expected Token type, if matches, consume it and get
	// next token, otherwise throws an runtime error.
	//
	std::shared_ptr<Token> match(Token::token_t type);

	//
	// next_token()
	// Returns the old Token and extracts the next Token.
	//
	std::shared_ptr<Token> next_token();

	//
	// parse_hornclauses()
	// Entrance of parsing a single horn clauses, if succeeded, the Hornclause buffer
	// will contains a hornclause sub-tree. Otherwise, it might contains partial corrected
	// subtree, checks buffer in CATCH block.
	//
	void parse_hornclauses();

	//
	// parse_head()
	// Parses the head and returns a node of Head.
	//
	std::shared_ptr<Head> parse_head();

	//
	// parse_body()
	// Parses the body and returns a node of Body.
	//
	std::shared_ptr<Body> parse_body();

	//
	// parse_predicate()
	// Parses the predicate and returns a node of Predicate.
	//
	std::shared_ptr<Predicate> parse_predicate();
	
	//
	// parse_symbol()
	// Parses the symbol and returns a node of Symbol.
	//
	std::shared_ptr<Symbol> parse_symbol();
};


#endif