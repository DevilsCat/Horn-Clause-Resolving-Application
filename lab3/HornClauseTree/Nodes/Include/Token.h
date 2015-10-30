// token.h : Declares token struct which program uses it to record semantic of string for Horn clause
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <memory>

#define TOKENIZE(a)		static_cast<Token::token_t>(a)

//
// struct Token
// a token struct type that has: a public enumerated type for the kind of token, which has the enumeration labels AND, COMMA, 
// LABEL, LEFTPAREN, NUMBER, RIGHTPAREN, SEPARATOR, and UNKNOWN; a public member variable of the enumerated type; a public 
//member variable of type (C++ style) string; and a public constructor that sets the first public member variable's value to
// UNKNOWN but leaves the second member variable as an empty string.
//
struct Token {
	//
	// enum token_t
	// Defines token type for this token struct. For each type, a 1 shifted value is assigment used for bit manipulation
	//
	enum token_t {
		LABEL		= 1,
		LEFTPAREN	= 2,
		NUMBER		= 4,
		RIGHTPAREN	= 8,
		SYMBOL		= 16,
		PREDICATE	= 32,
		BODY		= 64,
		HEAD		= 128,
		HORNCLAUSE	= 256,
		UNKNOW		= 512
	};

	// Stores token type for this Token object
	token_t type;

	// Stores token string for this Token object
	std::string label;

	// A container store the Token Pointor as children (Used to implement Token Tree)
	std::vector<std::shared_ptr<Token>> children;

	//
	// Token Constructor
	// Takes token type and string to construct this struct
	//
	Token(token_t t, std::string& s);

	//
	// Token Constructor
	//
	Token(token_t t);

	//
	// Token Default Constructor
	// Set Token as type Unknow, label empty
	//
	Token();

	//
	// Virtual Deconstructor
	// Make this struct polymorphic
	//
	virtual ~Token();

	//
	// operator== -- overloaded
	// Perform a token type check using int value. In fact this int value is the OR result from multiple token types
	// Usage example:
	//   Token token(LABEL, std::string("my_string"));
	//   assert(token == (Token::LABEL | Token::NUMBER));
	//
	bool operator==(const int& t);

	bool operator!=(const int& t);

	//
	// operator== -- overloaded
	// Perform a token type check using token_t enum.
	//
	bool operator==(const token_t& t);

	//
	// operator!=
	// Return false if this token is not the type of given token_t type
	//
	bool operator!=(const token_t& t);

	//
	// operator std::string()
	// Convert this Token type to a string using label
	//
    operator std::string() const;

	//
	// operator== -- lab 2
	// Compares two Token Objects, if labels are the same, returns true.
	//
	bool operator==(const Token& other);

	//
	// operaotr!= -- lab 2
	// Compares two Token Objects, if labels are not the same, returns true.
	//
	bool operator!=(const Token& other);

	//
	// addNode()
	// Adds a children node the this node, used to build a Token Tree.
	//
	void addNode(std::shared_ptr<Token> token);

	//
	// clear()
	// Clear the children of this node.
	//
	void clear();
	//
	//accept()
	//A virtual function that accepts visitor to do visitor routines.
	//
	virtual void accept(class Visitor& v);
};

#endif