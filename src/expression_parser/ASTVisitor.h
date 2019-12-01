#pragma once

struct BinaryOpNode;
struct UnaryOpNode;
struct IntegerNode;
struct AssignmentNode;
struct VariableNode;

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    virtual void visitBinaryOp(BinaryOpNode& node) = 0;
    virtual void visitUnaryOp(UnaryOpNode& node) = 0;
    virtual void visitInteger(IntegerNode& node) = 0;
    virtual void visitAssignment(AssignmentNode& node) = 0;
    virtual void visitVariable(VariableNode& node) = 0;
};
