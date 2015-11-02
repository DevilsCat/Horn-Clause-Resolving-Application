#include "stdafx.h"
#include "NumberToken.h"

NumberToken::NumberToken(std::string& s) :
    BaseToken(NUMBER, s), number(atoi(s.c_str()))
{}
