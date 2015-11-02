#include "stdafx.h"
#include "BaseNode.h"

BaseNode::BaseNode(const NodeType& type) :
    type_(type)
{}

BaseNode::~BaseNode() {}

void BaseNode::AddNode(std::shared_ptr<BaseNode> node_ptr) {
    children_.push_back(node_ptr);
}

void BaseNode::Clear() {
    children_.clear();
}