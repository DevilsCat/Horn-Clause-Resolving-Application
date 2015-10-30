#include "stdafx.h"
#include "TokenRoot.h"
#include "Visitor.h"

void TokenRoot::accept(Visitor& v){
	v.visit(this);
	for (std::vector<std::shared_ptr<Token>>::const_iterator it = children.begin(); it != children.end(); ++it) {
		std::dynamic_pointer_cast<Hornclause> (*it)->accept(v);
	}
}