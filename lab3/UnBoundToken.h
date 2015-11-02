#ifndef UNBOUND_TOKEN_H
#define UNBOUND_TOKEN_H
#include "LabelToken.h"

struct UnBoundToken : LabelToken {

    explicit UnBoundToken(const std::string& s);
};

#endif

