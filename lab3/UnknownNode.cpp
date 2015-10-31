#include "stdafx.h"
#include "UnknownNode.h"
#include "Visitor.h"

UnknownNode::UnknownNode() : 
    BaseNode(kUnknown) 
{}

void UnknownNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    v.OnPostVisit(this);
}