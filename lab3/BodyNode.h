#ifndef BODY_NODE_H
#define BODY_NODE_H
#include "BaseNode.h"
#include "Visitor.h"

struct BodyNode : BaseNode {

    explicit BodyNode();

    virtual void Accept(Visitor&) override;
};

#endif
