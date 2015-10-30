#include "stdafx.h"
#include "Hornclause.h"
#include "Visitor.h"

#define HEAD_POS 0
#define BODY_POS 1
#define SIZE_WITH_BODY 2

Hornclause::Hornclause() :
	Token(HORNCLAUSE)
{}

void Hornclause::accept(Visitor& v){
	v.visit(this);
	std::dynamic_pointer_cast<Head> (children[HEAD_POS])->accept(v);
	if (hasBody()){
		std::dynamic_pointer_cast<Body> (children[BODY_POS])->accept(v);
	}
}

bool Hornclause::hasBody(){
	return children.size() == SIZE_WITH_BODY;
}