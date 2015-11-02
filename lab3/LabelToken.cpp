#include "stdafx.h"
#include "LabelToken.h"

LabelToken::LabelToken(const std::string& s) :
    BaseToken(LABEL, s)
{}

LabelToken::LabelToken(const TokenType& type, const std::string& s) :
    BaseToken(type, s)
{}