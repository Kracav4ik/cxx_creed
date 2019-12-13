#pragma once

#include "expression_parser/ASTVisitor.h"
#include "expression_parser/ast/ASTNode.h"

#include <sstream>
#include <string>

class ASTNodeString : ASTVisitor {
public:
    ASTNodeString(const ASTNodePtr& node);
    std::string str() const;

private:
    void visitBinaryOp(const BinaryOpNode& node) override;
    void visitUnaryOp(const UnaryOpNode& node) override;
    void visitInteger(const IntegerNode& node) override;
    void visitString(const StringNode& node) override;
    void visitAssignment(const AssignmentNode& node) override;
    void visitVariable(const VariableNode& node) override;

    std::stringstream _buf;
};
