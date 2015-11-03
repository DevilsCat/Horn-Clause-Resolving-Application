#include "stdafx.h"
#include "BoundToken.h"
#include <ostream>
#include <sstream>
#include <string>

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