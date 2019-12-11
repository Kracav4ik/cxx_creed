#pragma once

#include "ASTEvent.h"
#include "expression_parser/ast/ASTNode.h"

struct BeginIfStmtEvent : public ASTEvent {
    explicit BeginIfStmtEvent(ASTNodePtr value);
    void visit(EventVisitor& visitor) override;

    ASTNodePtr expr;
};
