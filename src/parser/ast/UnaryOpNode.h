#pragma once

#include "ASTNode.h"

#include <string>

struct UnaryOpNode : ASTNode {
    UnaryOpNode(std::string op, ASTNodePtr subnode);
    void visit(ASTVisitor& visitor) override;

    std::string op;
    ASTNodePtr subnode;
};
