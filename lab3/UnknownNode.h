#ifndef UNKNOWN_NODE_H
#define UNKNOWN_NODE_H
#include "BaseNode.h"
#include "Visitor.h"

struct UnknownNode : BaseNode {

    explicit UnknownNode();

    virtual void Accept(Visitor&) override;
};

#endif
