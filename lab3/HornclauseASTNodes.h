// HornclauseASTNodes.h -- This files declares ASTNode family classes used to represent a horn clause AST tree.
// Created by Anqi Zhang, Yu Xiao, all right reserved.
//
#ifndef HORNCLAUSE_AST_NODES_H
#define HORNCLAUSE_AST_NODES_H
#include <vector>
#include <memory>
#include "Visitor.h"

// Declares command attributes of AST node family.
struct BaseNode {
    // Delcares all types of derived node class.
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

    // Stores type of derived node class.
    NodeType type_;

    // Stores the Token Pointors as children (Used to implement Token Tree)
    std::vector<std::shared_ptr<BaseNode>> children_;

    // Takes a reference of type of node so that parser can test on.
    BaseNode(const NodeType&);

    virtual ~BaseNode();

    // Adds a children node the this node, used to build a Parsing Tree.
    void AddNode(std::shared_ptr<BaseNode> node_ptr);

    // Clear the children of this node.
    void Clear();

    // A virtual function that accepts visitor to do visitor routines.
    virtual void Accept(Visitor&) = 0;
};

// Derived class of BaseNode that is the root node of abstract semantic tree of hornclauses.
struct RootNode : BaseNode {
    // Initializes this class, identifies itself as {kRoot} type.
    explicit RootNode();

    // A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    virtual void Accept(Visitor& v) override;
};

// Derived class of BaseNode that is the horn clause node of abstract semantic tree of hornclauses.
struct HornclauseNode : BaseNode {
    // Initializes this class, identifies itself as {kHornclause} type.
    explicit HornclauseNode();

    // Returns true if this horn clause contains {BodyNode}.
    bool HasBody() const;

    // A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    virtual void Accept(Visitor&) override;
};

// Derived class of BaseNode that is the horn clause node of abstract semantic tree of hornclauses.
struct HeadNode : BaseNode {
    // Initializes this class, identifies itself as {kHead} type.
    explicit HeadNode();

    // A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    virtual void Accept(Visitor&) override;
};

// Derived class of BaseNode that is the body node of abstract semantic tree of hornclauses.
struct BodyNode : BaseNode {
    // Initializes this class, identifies itself as {kBody} type.
    explicit BodyNode();

    // A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    virtual void Accept(Visitor&) override;
};

// Derived class of BaseNode that is the predicate node of abstract semantic tree of hornclauses.
struct PredicateNode : BaseNode {
    typedef std::vector<std::shared_ptr<BaseNode>>::const_iterator NodeIterator;

    // Initializes this class, identifies itself as {kPredicate} type.
    explicit PredicateNode();

    bool HasSymbolNodes(NodeIterator& it) const;

    std::shared_ptr<struct NameNode> GetNameNode(NodeIterator& it) const;

    std::shared_ptr<struct SymbolNode> GetSymbolNode(NodeIterator& it) const;

    std::shared_ptr<struct PredicateEntry> ToPredicateEntry() const;

    // A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    virtual void Accept(Visitor&) override;
};

// Derived class of BaseNode that is the name node of abstract semantic tree of hornclauses.
struct NameNode : BaseNode {
    // Stores {LabelToken}.
    std::shared_ptr<struct LabelToken> label_ptr_;

    // Initializes this class, identifies itself as {kLabel} type and stores the passed label token.
    explicit NameNode(std::shared_ptr<LabelToken> label_ptr);

    // A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    virtual void Accept(Visitor&) override;
};

// Derived class of BaseNode that is the symbol node of abstract semantic tree of hornclauses.
struct SymbolNode : BaseNode {
    // Stores {LabelToken} or {NumberToken}.
    std::shared_ptr<struct BaseToken> symbol_ptr_;

    // Initializes this class, identifies itself as {kSymbol} type and stores {LabelToken} or
    // {NumberToken} as semantic value to this node.
    explicit SymbolNode(std::shared_ptr<BaseToken> symbol_ptr);

    // A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    virtual void Accept(Visitor&) override;
};

// Derived class of BaseNode that is the unknown node of abstract semantic tree of hornclauses.
struct UnknownNode : BaseNode {
    // Initializes this class, identifies itself as {kUnknown} type.
    explicit UnknownNode();

    // A virtual function overrided from BaseNode, accept visitor to do visiting routines.
    virtual void Accept(Visitor&) override;
};

#endif