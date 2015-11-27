// HornclauseTokens.h -- This file declares horn clause token class family.
// Created by Anqi Zhang, Yu Xiao, all right reserved.
//
#ifndef HORNCLAUSE_TOKENS_H
#define HORNCLAUSE_TOKENS_H
#include <string>

// A token struct type that has: a public enumerated type for the kind of token, which has the enumeration labels AND, COMMA, 
// LABEL, LEFTPAREN, NUMBER, RIGHTPAREN, SEPARATOR, and UNKNOWN; a public member variable of the enumerated type; a public 
//member variable of type (C++ style) string; and a public constructor that sets the first public member variable's value to
// UNKNOWN but leaves the second member variable as an empty string.
struct BaseToken {
    // Declares token type for this token struct. For each type, a 1 shifted value is assigment used for bit manipulation
    enum TokenType {
        LABEL = 1,
        LEFTPAREN = 2,
        NUMBER = 4,
        RIGHTPAREN = 8,
        BOUND = 16,
        UNBOUND = 32,
        UNKNOWN = 64
    };

    // Stores token type for this Token object
    TokenType type;
    // Stores token string for this Token object
    std::string label;

    // Takes token type and string to construct this struct
    BaseToken(const TokenType& t, const std::string& s);

    // Set Token as type Unknown, label empty
    BaseToken();

    // Make this struct polymorphic
    virtual ~BaseToken();

    // Perform a token type check using int value. In fact this int value is the OR result from multiple token types
    // Usage example:
    //   Token token(LABEL, std::string("my_string"));
    //   assert(token == (Token::LABEL | Token::NUMBER));
    //
    bool operator==(const int& t) const;

    // Reverses the result of operator==.
    bool operator!=(const int& t) const;

    // Perform a token type check using token_t enum.
    bool operator==(const TokenType& t) const;

    // Return false if this token is not the type of given token_t type
    bool operator!=(const TokenType& t) const;

    // Convert this Token type to a string using label
    virtual operator const std::string() const;

    // Compares two Token Objects, if labels are the same, returns true.
    bool operator==(const BaseToken& other) const;

    // Compares two Token Objects, if labels are not the same, returns true.
    bool operator!=(const BaseToken& other) const;
};

// Derived struct of Token struct, classifies token as a Label
// name node in the abstract semantic tree of horn clauses, EBNF grammar :
struct LabelToken : BaseToken{
    // Initializes base class as {kLabel}.
    explicit LabelToken(const std::string& s);

    // Initializes base class to either {kBound} or {kUnBound}.
    explicit LabelToken(const TokenType& type, const std::string& s);
};

// Derived struct of LabelToken, contains a semantic value of a bounded
// varaible.
struct BoundToken : LabelToken {
    // Stores value of this bounded varialbe.
    int value;

    // Initializes base struct as {kBound}, and default value to 0.
    explicit BoundToken(const std::string& s);

    // Initializes base struct as {kBound}, and stores arbitrary integer value.
    BoundToken(const std::string&, int);

    // Returns "bounded_variable{value}" of this token.
    operator const std::string() const override;

    // Prints std::string of this struct.
    friend std::ostream& operator<< (std::ostream&, const BoundToken&);
};

// Derived struct of LabelToken, represents a unbounded variable in horn clause.
struct UnBoundToken : LabelToken {
    // Initializes base struct as {kUnBound}.
    explicit UnBoundToken(const std::string& s);
};


// Derived struct of Token struct, classifies token as a integer, and interpret stores the real uint value
struct NumberToken : BaseToken{
    // Stores the semantic value of this token
    unsigned number;

    // Initializes base struct as {kNumber}.
    explicit  NumberToken(std::string& s);
};

// This Comparator specifies how Token object stores in STL container.
struct TokenComparator {
    bool operator()(const BaseToken& lhs, const BaseToken& rhs) const;
};

// Uses to find the Token inside the vector
struct TokenFinder {
    // Takes a Token reference and stores it for later comparing.
    TokenFinder(const BaseToken& t);

    // Returns true if Token labels are the same.
    bool operator()(const BaseToken& t) const;

    // Variables to store the left hand Token.
    const BaseToken t_;
};

#endif