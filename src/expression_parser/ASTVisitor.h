#pragma once

struct BinaryOpNode;
struct UnaryOpNode;
struct IntegerNode;
struct AssignmentNode;
struct VariableNode;

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visitBinaryOp(const BinaryOpNode& node) = 0;
    virtual void visitUnaryOp(const UnaryOpNode& node) = 0;
    virtual void visitInteger(const IntegerNode& node) = 0;
    virtual void visitAssignment(const AssignmentNode& node) = 0;
    virtual void visitVariable(const VariableNode& node) = 0;
};
