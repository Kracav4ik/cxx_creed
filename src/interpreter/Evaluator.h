#pragma once

#include "expression_parser/ASTVisitor.h"
#include "expression_parser/ast/ASTNode.h"

#include "interpreter/types/ValueFwd.h"

class Scope;
class Printer;

class Evaluator : ASTVisitor {
public:
    Evaluator(Scope& scope, Printer& printer);

    static ValuePtr evaluate(const ASTNodePtr& node, Scope& scope, Printer& printer);

private:
    void visitBinaryOp(BinaryOpNode& node) override;
    void visitUnaryOp(UnaryOpNode& node) override;
    void visitInteger(IntegerNode& node) override;
    void visitAssignment(AssignmentNode& node) override;
    void visitVariable(VariableNode& node) override;

    ValuePtr _result;
    Scope& _scope;
    Printer& _printer;
};
