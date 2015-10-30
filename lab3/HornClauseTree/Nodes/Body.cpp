#include "stdafx.h"
#include "Body.h"
#include "Visitor.h"

Body::Body() :
	Token(BODY)
{}

void Body::accept(Visitor& v){
	v.visit(this);
	for (std::vector<std::shared_ptr<Token>>::const_iterator it = children.begin(); it != children.end(); ++it) {
		std::dynamic_pointer_cast<Predicate> (*it)->accept(v);
	}
}