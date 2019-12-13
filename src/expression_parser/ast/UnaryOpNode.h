#pragma once

#include "ASTNode.h"

#include <string>

struct UnaryOpNode : ASTNode {
    UnaryOpNode(std::string op, std::string text, ASTNodePtr subnode);
    void visit(ASTVisitor& visitor) const override;

    std::string op;
    std::string text;
    ASTNodePtr subnode;
};
