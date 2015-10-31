#ifndef HEAD_NODE_H
#define HEAD_NODE_H
#include "BaseNode.h"
#include "Visitor.h"

struct HeadNode : BaseNode {

    explicit HeadNode();

    virtual void Accept(Visitor&) override;
};

#endif
