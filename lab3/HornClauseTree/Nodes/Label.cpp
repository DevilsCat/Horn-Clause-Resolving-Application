#include "stdafx.h"
#include "Label.h"
#include "Visitor.h"
Label::Label(std::string& s) :
	Token(LABEL, s)
{}

void Label::accept(Visitor& v){
	v.visit(this);
}