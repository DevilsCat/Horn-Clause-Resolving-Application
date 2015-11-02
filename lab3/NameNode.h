#ifndef NAME_NODE_H
#define NAME_NODE_H
#include "BaseNode.h"
#include "LabelToken.h"
#include "Visitor.h"

struct NameNode : BaseNode {

    std::shared_ptr<LabelToken> label_ptr_;

    explicit NameNode(std::shared_ptr<LabelToken> label_ptr);

    virtual void Accept(Visitor&) override;
};

#endif
