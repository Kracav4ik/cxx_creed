#pragma once

#include "ASTEvent.h"
#include "expression_parser/ast/ASTNode.h"

struct BeginIfDeclEvent : public ASTEvent {
    explicit BeginIfDeclEvent(ASTNodePtr value);
    void visit(EventVisitor& visitor) override;

    ASTNodePtr expr;
};
