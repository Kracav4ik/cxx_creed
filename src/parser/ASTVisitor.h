#pragma once

struct BinaryOpNode;
struct IntegerNode;
class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visitBinaryOp(BinaryOpNode& node) = 0;
    virtual void visitInteger(IntegerNode& node) = 0;
};
