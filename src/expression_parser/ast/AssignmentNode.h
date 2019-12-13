#pragma once

#include "ASTNode.h"

struct AssignmentNode : ASTNode {
    AssignmentNode(ASTNodePtr left, ASTNodePtr right);
    void visit(ASTVisitor& visitor) const override;

    ASTNodePtr left;
    ASTNodePtr right;
};
