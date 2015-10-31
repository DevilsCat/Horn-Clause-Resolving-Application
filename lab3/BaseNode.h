#ifndef BASE_NODE_H
#define BASE_NODE_H
#include <vector>
#include <memory>
#include "Visitor.h"

struct BaseNode {
    enum NodeType {
        kRoot = 0,
        kHornclause,
        kHead,
        kBody,
        kPredicate,
        kName,
        kSymbol,
        kUnknown
    };

    NodeType type_;

    // Stores the Token Pointors as children (Used to implement Token Tree)
    std::vector<std::shared_ptr<BaseNode>> children_;

    BaseNode(const NodeType&);

    virtual ~BaseNode();

    //
    // AddNode()
    // Adds a children node the this node, used to build a Parsing Tree.
    //
    void AddNode(std::shared_ptr<BaseNode> node_ptr);

    //
    // clear()
    // Clear the children of this node.
    //
    void Clear();

    //
    //accept()
    //A virtual function that accepts visitor to do visitor routines.
    //
    virtual void Accept(Visitor&) = 0;
};

#endif