#include "stdafx.h"
#include "Head.h"
#include "Visitor.h"

Head::Head() :
	Token(HEAD)
{}

void Head::accept(Visitor& v){
	v.visit(this);
	for (std::vector<std::shared_ptr<Token>>::const_iterator it = children.begin(); it != children.end(); ++it) {
		std::dynamic_pointer_cast<Predicate> (*it)->accept(v);
	}
}