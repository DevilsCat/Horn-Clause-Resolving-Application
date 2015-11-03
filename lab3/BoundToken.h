#ifndef BOUND_TOKEN_H
#define BOUND_TOKEN_H
#include "LabelToken.h"

struct BoundToken : LabelToken {
    int value;
    explicit BoundToken(const std::string& s);
	BoundToken(const std::string&, int);
    operator const std::string() const override;
    friend std::ostream& operator<< (std::ostream&, const BoundToken&);
};

#endif
