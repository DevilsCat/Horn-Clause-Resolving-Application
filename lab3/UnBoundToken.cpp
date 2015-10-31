#include "stdafx.h"
#include "UnBoundToken.h"

UnBoundToken::UnBoundToken(const std::string& s) : 
    LabelToken(UNBOUND, s) 
{}