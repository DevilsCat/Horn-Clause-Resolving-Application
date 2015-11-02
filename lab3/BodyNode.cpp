#include "stdafx.h"
#include "BodyNode.h"
#include "Visitor.h"
#include "PredicateNode.h"

BodyNode::BodyNode(): 
    BaseNode(kBody) 
{}

void BodyNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    for (std::vector<std::shared_ptr<BaseNode>>::const_iterator it = children_.begin(); it != children_.end(); ++it) {
        std::dynamic_pointer_cast<PredicateNode>(*it)->Accept(v);
    }
    v.OnPostVisit(this);
}