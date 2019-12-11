#pragma once

#include "ASTEvent.h"
#include "expression_parser/ast/ASTNode.h"

struct BeginWhileStmtEvent  : public ASTEvent {
    explicit BeginWhileStmtEvent(ASTNodePtr expr);
    void visit(EventVisitor& visitor) override;

    ASTNodePtr expr;
};
