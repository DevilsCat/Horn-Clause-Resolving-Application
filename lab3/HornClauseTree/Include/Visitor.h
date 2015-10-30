// Visitor.h : Delare Visitor class that allows user to visit every node of the horn clause tree.
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef VISITOR_H
#define VISITOR_H
//
//class Visitor
//
//
class Visitor
{
public:

	virtual ~Visitor(){}
	
	virtual void visit(struct Token* node){}

	virtual void visit(struct TokenRoot* node){}

	virtual void visit(struct Hornclause* node){}

	virtual	void visit(struct Head* node){}

	virtual void visit(struct Body* node){}

	virtual	void visit(struct Predicate* node){}

	virtual void visit(struct Symbol* node){}

	virtual void visit(struct Label* node){}

	virtual void visit(struct Number* node){}

private:

};
#endif