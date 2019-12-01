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
    void visitBinaryOp(BinaryOpNode& node) override;
    void visitUnaryOp(UnaryOpNode& node) override;
    void visitInteger(IntegerNode& node) override;
    void visitAssignment(AssignmentNode& node) override;
    void visitVariable(VariableNode& node) override;

    std::stringstream _buf;
};
