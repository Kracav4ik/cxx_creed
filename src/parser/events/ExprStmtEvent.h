#pragma once
#include "ASTEvent.h"
#include "expression_parser/ast/ASTNode.h"

struct ExprStmtEvent : public ASTEvent {
    explicit ExprStmtEvent(ASTNodePtr value);
    void visit(EventVisitor& visitor) override;

    ASTNodePtr expr;
};
