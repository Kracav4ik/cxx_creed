#pragma once

#include "ASTNode.h"

struct IntegerNode : ASTNode {
    explicit IntegerNode(int value);
    void visit(ASTVisitor& visitor) override;

    int value;
};
