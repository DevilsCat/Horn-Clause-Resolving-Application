#ifndef BOUND_TOKEN_H
#define BOUND_TOKEN_H
#include "LabelToken.h"

struct BoundToken : LabelToken {

    explicit BoundToken(const std::string& s);
};

#endif
