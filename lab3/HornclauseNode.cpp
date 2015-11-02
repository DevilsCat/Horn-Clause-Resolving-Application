#include "stdafx.h"
#include "HornclauseNode.h"
#include "Visitor.h"
#include "HeadNode.h"
#include "BodyNode.h"

#define HEAD_POS 0
#define BODY_POS 1
#define SIZE_WITH_BODY 2

HornclauseNode::HornclauseNode(): 
    BaseNode(kHornclause) 
{}

bool HornclauseNode::HasBody() const {
    return children_.size() == SIZE_WITH_BODY;
}

void HornclauseNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    std::dynamic_pointer_cast<HeadNode>(children_[HEAD_POS])->Accept(v);
    if (HasBody()) {
        std::dynamic_pointer_cast<BodyNode>(children_[BODY_POS])->Accept(v);
    }
    v.OnPostVisit(this);
}