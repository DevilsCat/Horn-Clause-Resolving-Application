#ifndef HORNCLAUSE_NODE_H
#define HORNCLAUSE_NODE_H
#include "BaseNode.h"
#include "Visitor.h"

struct HornclauseNode : BaseNode {

    explicit HornclauseNode();

    bool HasBody() const;

    virtual void Accept(Visitor&) override;
};

#endif
