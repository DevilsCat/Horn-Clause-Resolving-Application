#include "stdafx.h"
#include "RootNode.h"
#include "Visitor.h"
#include "HornclauseNode.h"
RootNode::RootNode(): 
    BaseNode(kRoot) 
{}

void RootNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    for (std::vector<std::shared_ptr<BaseNode>>::const_iterator it = children_.begin(); it != children_.end(); ++it) {
        std::dynamic_pointer_cast<HornclauseNode>(*it)->Accept(v);
    }
    v.OnPostVisit(this);
}