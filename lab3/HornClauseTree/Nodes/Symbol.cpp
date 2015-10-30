#include "stdafx.h"
#include "Symbol.h"
#include "Visitor.h"
#include "Number.h"
#include "Label.h"

Symbol::Symbol() :
	Token(SYMBOL)
{}

void Symbol::accept(Visitor& v){
	v.visit(this);
	for (std::vector<std::shared_ptr<Token>>::const_iterator it = children.begin(); it != children.end(); ++it) {
		if ((*it)->type == NUMBER){
			std::dynamic_pointer_cast<Number>(*it)->accept(v);
		}
		else{
			std::dynamic_pointer_cast<Label>(*it)->accept(v);
		}
	}
}