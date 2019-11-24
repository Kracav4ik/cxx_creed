#pragma once

#include "parser/ASTVisitor.h"
#include "parser/ast/ASTNode.h"

class Evaluator : ASTVisitor {
public:
    static int evaluate(const ASTNodePtr& node);

private:
    void visitBinaryOp(BinaryOpNode& node) override;
    void visitUnaryOp(UnaryOpNode& node) override;
    void visitInteger(IntegerNode& node) override;

    int _result = 0;
};
