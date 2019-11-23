#pragma once

#include "ASTNode.h"

#include <string>

struct BinaryOpNode : ASTNode {
    BinaryOpNode(std::string op, ASTNodePtr left, ASTNodePtr right);
    void visit(ASTVisitor& visitor) override;

    std::string op;
    ASTNodePtr left;
    ASTNodePtr right;
};
