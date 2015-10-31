#include "stdafx.h"
#include "LabelToken.h"

LabelToken::LabelToken(const std::string& s) :
    LabelToken(kBasic, s)
{}

LabelToken::LabelToken(const LabelType& type, const std::string& s) :
    BaseToken(LABEL, s), type_(type)
{}