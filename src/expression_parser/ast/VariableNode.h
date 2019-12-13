#pragma once

#include "ASTNode.h"

struct VariableNode : ASTNode {
    explicit VariableNode(std::string value);
    void visit(ASTVisitor& visitor) const override;

    std::string var_name;
};
