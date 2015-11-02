#ifndef SYMBOL_NODE_H
#define SYMBOL_NODE_H
#include "BaseNode.h"
#include "BaseToken.h"
#include "Visitor.h"

struct SymbolNode : BaseNode {
    std::shared_ptr<BaseToken> symbol_ptr_;

    explicit SymbolNode(std::shared_ptr<BaseToken> symbo_ptr);

    virtual void Accept(Visitor&) override;
};

#endif
