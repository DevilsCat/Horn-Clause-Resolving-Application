#ifndef PREDICATE_NODE_H
#define PREDICATE_NODE_H
#include "BaseNode.h"
#include "NameNode.h"
#include "SymbolNode.h"
#include "PredicateST.h"
#include "Visitor.h"

struct PredicateNode : BaseNode {
    typedef std::vector<std::shared_ptr<BaseNode>>::const_iterator NodeIterator;
    
    explicit PredicateNode();

    bool HasSymbolNodes(NodeIterator& it) const;

    std::shared_ptr<NameNode> GetNameNode(NodeIterator& it);

    std::shared_ptr<SymbolNode> GetSymbolNode(NodeIterator& it);

    std::shared_ptr<PredicateST> MakePredicateST();

    virtual void Accept(Visitor&) override;
};

#endif
