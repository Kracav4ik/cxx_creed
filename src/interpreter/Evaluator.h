#pragma once

#include "expression_parser/ASTVisitor.h"
#include "expression_parser/ast/ASTNode.h"

class Scope;
class Printer;

class Evaluator : ASTVisitor {
public:
    Evaluator(Scope& scope, Printer& printer);

    static int evaluate(const ASTNodePtr& node, Scope& scope, Printer& printer);
    static bool is_true(int val);

private:
    void visitBinaryOp(BinaryOpNode& node) override;
    void visitUnaryOp(UnaryOpNode& node) override;
    void visitInteger(IntegerNode& node) override;
    void visitAssignment(AssignmentNode& node) override;
    void visitVariable(VariableNode& node) override;

    int _result = 0;
    Scope& _scope;
    Printer& _printer;
};
