// HornclauseASTNodes.cpp -- This files defines ASTNode family classes used to represent a horn clause AST tree.
// Created by Anqi Zhang, Yu Xiao, all right reserved.
//
#include "stdafx.h"
#include "HornclauseASTNodes.h"
#include "HornclauseTokens.h"
#include "PredicateEntry.h"

// Struct BaseNode Implementation.
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

// Struct RootNode Implementation.
RootNode::RootNode() :
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

// Struct HornclauseNode Implementation.
#define HEAD_POS 0
#define BODY_POS 1
#define SIZE_WITH_BODY 2

HornclauseNode::HornclauseNode() :
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

// Struct HeadNode Implementation.
HeadNode::HeadNode() :
    BaseNode(kHead)
{}

void HeadNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    for (std::vector<std::shared_ptr<BaseNode>>::const_iterator it = children_.begin(); it != children_.end(); ++it) {
        std::dynamic_pointer_cast<PredicateNode> (*it)->Accept(v);
    }
    v.OnPostVisit(this);
}

// Struct BodyNode Implementation.
BodyNode::BodyNode() :
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

// Struct PredicateNode Implementation.
PredicateNode::PredicateNode() :
    BaseNode(kPredicate)
{}

bool PredicateNode::HasSymbolNodes(NodeIterator& it) const {
    return it != children_.begin() && it != children_.end();
}

std::shared_ptr<NameNode> PredicateNode::GetNameNode(NodeIterator& it) const{
    if (it != children_.begin()) { return std::shared_ptr<NameNode>(); }
    return std::dynamic_pointer_cast<NameNode>(*(it++));
}

std::shared_ptr<SymbolNode> PredicateNode::GetSymbolNode(NodeIterator& it) const{
    return std::dynamic_pointer_cast<SymbolNode>(*(it++));
}

std::shared_ptr<PredicateEntry> PredicateNode::ToPredicateEntry() const{
    NodeIterator it = children_.begin();
    std::shared_ptr<PredicateEntry> p_entry = std::make_shared<PredicateEntry>(*GetNameNode(it)->label_ptr_);
    while (HasSymbolNodes(it)) {
        p_entry->symbols.push_back(GetSymbolNode(it)->symbol_ptr_.get());
    }
    return p_entry;
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

// Struct NameNode Implementation.
NameNode::NameNode(std::shared_ptr<LabelToken> label_ptr) :
    BaseNode(kName), label_ptr_(label_ptr)
{}

void NameNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    v.OnPostVisit(this);
}

// Struct SymbolNode Implementation.
SymbolNode::SymbolNode(std::shared_ptr<BaseToken> symbo_ptr) :
    BaseNode(kSymbol), symbol_ptr_(symbo_ptr)
{}

void SymbolNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    v.OnPostVisit(this);
}

// Struct UnknownNode Implementation.
UnknownNode::UnknownNode() :
    BaseNode(kUnknown)
{}

void UnknownNode::Accept(Visitor& v) {
    v.OnPreVisit(this);
    v.OnVisit(this);
    v.OnPostVisit(this);
}