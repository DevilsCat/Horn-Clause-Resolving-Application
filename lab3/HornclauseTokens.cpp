// HornclauseTokens.cpp -- This file defines horn clause token class family.
// Created by Anqi Zhang, Yu Xiao, copyright preserved.
//
#include "stdafx.h"
#include "HornclauseTokens.h"
#include <sstream>

// struct BaseToken Implementation.
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

// struct LabelToken implementation.
LabelToken::LabelToken(const std::string& s) :
    BaseToken(LABEL, s)
{}

LabelToken::LabelToken(const TokenType& type, const std::string& s) :
    BaseToken(type, s)
{}

// struct BoundToken implementation.
BoundToken::BoundToken(const std::string& s) :
LabelToken(BOUND, s), value(0)
{}

BoundToken::BoundToken(const std::string& s, int i) :
LabelToken(BOUND, s), value(i)
{}

BoundToken::operator const std::string() const {
    std::ostringstream oss;
    oss << label << "{" << value << "}";
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const BoundToken& t) {
    os << static_cast<const std::string>(t);
    return os;
}

// struct UnBoundToken implementation.
UnBoundToken::UnBoundToken(const std::string& s) :
LabelToken(UNBOUND, s)
{}

// strcut NumberToken implementation.
NumberToken::NumberToken(std::string& s) :
BaseToken(NUMBER, s), number(atoi(s.c_str()))
{}

// struct TokenComparator/TokenFinder implemenation.
bool TokenComparator::operator()(const BaseToken& lhs, const BaseToken& rhs) const {
    return lhs.label < rhs.label;  // compare the Tokens label.
}

TokenFinder::TokenFinder(const BaseToken& t) : t_(t) {}


bool TokenFinder::operator()(const BaseToken& t) const {
    return t.label == t_.label;
}