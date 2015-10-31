#include "stdafx.h"
#include "SymbolNode.h"
#include "Visitor.h"

SymbolNode::SymbolNode(std::shared_ptr<BaseToken> symbo_ptr) : 
    BaseNode(kSymbol), symbol_ptr_(symbo_ptr) 
{}

void SymbolNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    v.OnPostVisit(this);
}