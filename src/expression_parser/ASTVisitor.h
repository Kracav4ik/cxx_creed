#pragma once

struct BinaryOpNode;
struct UnaryOpNode;
struct IntegerNode;
class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visitBinaryOp(BinaryOpNode& node) = 0;
    virtual void visitUnaryOp(UnaryOpNode& node) = 0;
    virtual void visitInteger(IntegerNode& node) = 0;
};
