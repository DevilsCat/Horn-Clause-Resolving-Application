#include "stdafx.h"
#include "PredicateNode.h"
#include "Visitor.h"

PredicateNode::PredicateNode(): 
    BaseNode(kPredicate) 
{}

bool PredicateNode::HasSymbolNodes(NodeIterator& it) const {
    return it != children_.begin() && it != children_.end();
}

std::shared_ptr<NameNode> PredicateNode::GetNameNode(NodeIterator& it) {
    if (it != children_.begin()) { return std::shared_ptr<NameNode>(); }
    return std::dynamic_pointer_cast<NameNode>(*(it++));
}

std::shared_ptr<SymbolNode> PredicateNode::GetSymbolNode(NodeIterator& it) {
    return std::dynamic_pointer_cast<SymbolNode>(*(it++));
}

std::shared_ptr<PredicateST> PredicateNode::MakePredicateST() {
    // TODO: Implement this to generate PredicateST.
    return std::shared_ptr<PredicateST>();
}

void PredicateNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    NodeIterator it = children_.begin();
    GetNameNode(it)->Accept(v);
    while (HasSymbolNodes(it)) {
        GetSymbolNode(it)->Accept(v);
    }
    v.OnPostVisit(this);
}