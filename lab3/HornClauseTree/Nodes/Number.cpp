#include "stdafx.h"
#include "Number.h"
#include "Visitor.h"

#define DEFAULT_NUMBER      0

Number::Number(std::string& s) :
Token(NUMBER, s), number(DEFAULT_NUMBER)
{
	std::istringstream iss(s); // convert string to number.
	iss >> number;
}

void Number::accept(Visitor& v){
	v.visit(this);
}