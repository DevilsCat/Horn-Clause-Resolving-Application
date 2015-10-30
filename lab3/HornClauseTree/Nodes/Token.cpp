#include "stdafx.h"
#include "Token.h"

#include "Visitor.h"

Token::Token(token_t t, std::string& s) :
	type(t), label(s)
{}

Token::Token(token_t t) :
	type(t), label()
{}

Token::Token() :
	type(UNKNOW), label()
{}

Token::~Token()
{}

bool Token::operator==(const int& t) {
	return *this == TOKENIZE(t);
}

bool Token::operator!=(const int& t) {
	return !(*this == t);
}

bool Token::operator==(const token_t& t) {
	return (static_cast<int>(type)& static_cast<int>(t)) != 0;
}

bool Token::operator!=(const token_t& t) {
	return !(*this == t);
}

Token::operator std::string() const{
	return label;
}

bool Token::operator==(const Token& other) {
	return label == other.label;
}

bool Token::operator!=(const Token& other) {
	return !(*this == other);
}

void Token::addNode(std::shared_ptr<Token> token) {
	children.push_back(token);
}

void Token::clear() {
	children.clear();
}

void Token::accept(Visitor& v){
	v.visit(this);
}