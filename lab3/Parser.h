// Parser.h : Declares a Parser class performing parsing for one layer formatted output horn clause
// Created by Anqi Zhang (439754), and Yu Xiao (439734), all right reserved.
//
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <memory>
#include "scanner.h"
#include "HornclauseASTNodes.h"
#include "HornclauseTokens.h"

// Pareses the input raw horn clauses (both well and bad formatted), and can perform semantic analysis.
// Sample Usage:
//   Parser p(input_filename, output_filename);
//   int ret = p.parse();
//   // ... check ret and error code
class Parser{
    typedef BaseToken::TokenType TokenType;
public:
	// Takes a reference file name string used to open an input file stream.
	Parser(std::istream& is);

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
	int Parse();

	// Get the token tree data structure this Parser.
	// This method is for the after processing of input horn clauses.
	std::shared_ptr<RootNode> root() const;

private:
	// Matches the expected Token type, if matches, consume it and get
	// next token, otherwise throws an runtime error.
	std::shared_ptr<BaseToken> match(TokenType type);

	// Entrance of parsing a single horn clauses, if succeeded, the Hornclause buffer
	// will contains a hornclause sub-tree. Otherwise, it might contains partial corrected
	// subtree, checks buffer in CATCH block.
	std::shared_ptr<HornclauseNode> ParseHornclause();

	// Parses single head and returns a node of Head.
	std::shared_ptr<HeadNode> ParseSinglePredHead();

    // Parses a multiple predicate head and returns a {HeadNode}.
    std::shared_ptr<HeadNode> ParseMultiPredHead();

	// Parses the body and returns a node of Body.
	std::shared_ptr<BodyNode> ParseBody();

	// Parses the predicate and returns a node of Predicate.
	std::shared_ptr<PredicateNode> ParsePredicate();
	
    // Parses the name and returns a node of Name
    std::shared_ptr<NameNode> ParseName();

	// Parses the symbol and returns a node of Symbol.
	std::shared_ptr<SymbolNode> ParseSymbol();

    // An ifstream contains lines of content for extracting horn clause
    std::istream& is_;

    // Scanner Object which uses to extract tokens from ifstream and store as a pointer
    Scanner scanner_;

    // A Token Tree entering point.
    std::shared_ptr<RootNode> root_;
};


#endif