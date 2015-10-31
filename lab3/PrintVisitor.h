#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H
#include "Visitor.h"
#include <string>

class PrintVisitor : public Visitor {
public:
    virtual void OnPreVisit(HornclauseNode*) override;
    virtual void OnPreVisit(BodyNode*) override;
    virtual void OnPreVisit(PredicateNode*) override;
    virtual void OnVisit(SymbolNode*) override;
    virtual void OnVisit(NameNode*) override;
    virtual void OnPostVisit(HornclauseNode*) override;
    virtual void OnPostVisit(HeadNode*) override;
    virtual void OnPostVisit(BodyNode*) override;
    virtual void OnPostVisit(PredicateNode*) override;
};

#endif
