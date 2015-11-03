#include "stdafx.h"
#include "BaseToken.h"

BaseToken::BaseToken(const TokenType& t, const std::string& s) :
	type(t), label(s)
{}

BaseToken::BaseToken() :
	type(UNKNOWN), label()
{}

BaseToken::~BaseToken()
{}

bool BaseToken::operator==(const int& t) const {
    return *this == static_cast<TokenType>(t);
}

bool BaseToken::operator!=(const int& t) const {
	return !(*this == t);
}

bool BaseToken::operator==(const TokenType& t) const {
	return (static_cast<int>(type)& static_cast<int>(t)) != 0;
}

bool BaseToken::operator!=(const TokenType& t) const {
	return !(*this == t);
}

BaseToken::operator const std::string() const{
	return label;
}

bool BaseToken::operator==(const BaseToken& other) const {
	return label == other.label;
}

bool BaseToken::operator!=(const BaseToken& other) const {
	return !(*this == other);
}