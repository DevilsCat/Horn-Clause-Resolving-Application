#include "stdafx.h"
#include "Utils.h"
#include "PrintVisitor.h"
#include "HornclauseASTNodes.h"
#include "HornclauseTokens.h"
#include <iostream>

void PrintVisitor::OnPreVisit(HornclauseNode*) {
    std::cout << Encode("(");
}

void PrintVisitor::OnPreVisit(BodyNode*) {
    std::cout << Encode("(");
}

void PrintVisitor::OnPreVisit(PredicateNode*) {
    std::cout << Encode("(");
}

void PrintVisitor::OnVisit(SymbolNode* node) {
    std::cout << Encode(*(node->symbol_ptr_));
}

void PrintVisitor::OnVisit(NameNode* node) {
    std::cout << Encode(*(node->label_ptr_));
}

void PrintVisitor::OnPostVisit(HornclauseNode*) {
    std::cout << Encode(")") << std::endl;
}

void PrintVisitor::OnPostVisit(HeadNode*) {}

void PrintVisitor::OnPostVisit(BodyNode*) {
    std::cout << Encode(")");
}

void PrintVisitor::OnPostVisit(PredicateNode*) {
    std::cout << Encode(")");
}
