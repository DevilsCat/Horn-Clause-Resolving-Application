// token.h : Declares token struct which program uses it to record semantic of string for Horn clause
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef BASE_TOKEN_H
#define BASE_TOKEN_H

#include <vector>



//
// struct Token
// a token struct type that has: a public enumerated type for the kind of token, which has the enumeration labels AND, COMMA, 
// LABEL, LEFTPAREN, NUMBER, RIGHTPAREN, SEPARATOR, and UNKNOWN; a public member variable of the enumerated type; a public 
//member variable of type (C++ style) string; and a public constructor that sets the first public member variable's value to
// UNKNOWN but leaves the second member variable as an empty string.
//
struct BaseToken {
	//
	// enum token_t
	// Defines token type for this token struct. For each type, a 1 shifted value is assigment used for bit manipulation
	//
	enum TokenType {
		LABEL       = 1,
		LEFTPAREN   = 2,
		NUMBER      = 4,
		RIGHTPAREN  = 8,
        BOUND       = 16,
        UNBOUND     = 32,
		UNKNOWN     = 64
	};

	// Stores token type for this Token object
    TokenType type;

	// Stores token string for this Token object
	std::string label;

	//
	// Token Constructor
	// Takes token type and string to construct this struct
	//
    BaseToken(const TokenType& t, const std::string& s);

	//
	// Token Default Constructor
	// Set Token as type Unknown, label empty
	//
	BaseToken();

	//
	// Virtual Deconstructor
	// Make this struct polymorphic
	//
	virtual ~BaseToken();

	//
	// operator== -- overloaded
	// Perform a token type check using int value. In fact this int value is the OR result from multiple token types
	// Usage example:
	//   Token token(LABEL, std::string("my_string"));
	//   assert(token == (Token::LABEL | Token::NUMBER));
	//
	bool operator==(const int& t) const;

	bool operator!=(const int& t) const;

	//
	// operator== -- overloaded
	// Perform a token type check using token_t enum.
	//
    bool operator==(const TokenType& t) const;

	//
	// operator!=
	// Return false if this token is not the type of given token_t type
	//
    bool operator!=(const TokenType& t) const;

	//
	// operator std::string()
	// Convert this Token type to a string using label
	//
    virtual operator const std::string() const;

	//
	// operator== -- lab 2
	// Compares two Token Objects, if labels are the same, returns true.
	//
	bool operator==(const BaseToken& other) const;

	//
	// operaotr!= -- lab 2
	// Compares two Token Objects, if labels are not the same, returns true.
	//
	bool operator!=(const BaseToken& other) const;
};

#endif