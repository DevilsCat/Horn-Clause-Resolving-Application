#include "stdafx.h"
#include "NameNode.h"
#include "Visitor.h"

NameNode::NameNode(std::shared_ptr<LabelToken> label_ptr) :
    BaseNode(kName), label_ptr_(label_ptr)
{}

void NameNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    v.OnPostVisit(this);
}