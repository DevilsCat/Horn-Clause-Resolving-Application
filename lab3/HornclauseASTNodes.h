#ifndef HORNCLAUSE_AST_NODES_H
#define HORNCLAUSE_AST_NODES_H
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

struct HornclauseNode : BaseNode {

    explicit HornclauseNode();

    bool HasBody() const;

    virtual void Accept(Visitor&) override;
};

struct HeadNode : BaseNode {

    explicit HeadNode();

    virtual void Accept(Visitor&) override;
};

struct BodyNode : BaseNode {

    explicit BodyNode();

    virtual void Accept(Visitor&) override;
};

struct PredicateNode : BaseNode {
    typedef std::vector<std::shared_ptr<BaseNode>>::const_iterator NodeIterator;

    explicit PredicateNode();

    bool HasSymbolNodes(NodeIterator& it) const;

    std::shared_ptr<struct NameNode> GetNameNode(NodeIterator& it) const;

    std::shared_ptr<struct SymbolNode> GetSymbolNode(NodeIterator& it) const;

    std::shared_ptr<struct PredicateEntry> ToPredicateEntry() const;

    virtual void Accept(Visitor&) override;
};

struct NameNode : BaseNode {

    std::shared_ptr<struct LabelToken> label_ptr_;

    explicit NameNode(std::shared_ptr<LabelToken> label_ptr);

    virtual void Accept(Visitor&) override;
};

struct SymbolNode : BaseNode {
    std::shared_ptr<struct BaseToken> symbol_ptr_;

    explicit SymbolNode(std::shared_ptr<BaseToken> symbo_ptr);

    virtual void Accept(Visitor&) override;
};

struct UnknownNode : BaseNode {

    explicit UnknownNode();

    virtual void Accept(Visitor&) override;
};

#endif