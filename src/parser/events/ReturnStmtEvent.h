#pragma once

#include "ASTEvent.h"
#include "expression_parser/ast/ASTNode.h"

struct ReturnStmtEvent : public ASTEvent {
    explicit ReturnStmtEvent(ASTNodePtr value);
    void visit(EventVisitor& visitor) override;

    ASTNodePtr value;
};
