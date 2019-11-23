#pragma once

#include <memory>

class ASTVisitor;

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void visit(ASTVisitor& visitor) = 0;
};

using ASTNodePtr = std::unique_ptr<ASTNode>;
