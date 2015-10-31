// TokenRoot.h : Declares RootNode struct, which is the derived class to BaseNode, and uses it to record semantic of root node of 
// the hornclauses tree. 
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef ROOT_NODE_H
#define ROOT_NODE_H
#include "BaseNode.h"
#include "Visitor.h"

//
// struct RootNode
// a derived class of BaseNode struct type that is the root node of abstract semantic tree of hornclauses.
//
struct RootNode : BaseNode {
    explicit RootNode();

    //
    //accept()
    //A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    //
    virtual void Accept(Visitor& v) override;
};

#endif
