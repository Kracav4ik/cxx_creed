#pragma once

#include "ASTEvent.h"
#include "expression_parser/ast/ASTNode.h"

struct BeginWhileDeclEvent  : public ASTEvent {
    explicit BeginWhileDeclEvent(ASTNodePtr expr);
    void visit(EventVisitor& visitor) override;

    ASTNodePtr expr;
};
