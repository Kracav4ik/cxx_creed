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
    void visitBinaryOp(const BinaryOpNode& node) override;
    void visitUnaryOp(const UnaryOpNode& node) override;
    void visitInteger(const IntegerNode& node) override;
    void visitString(const StringNode& node) override;
    void visitAssignment(const AssignmentNode& node) override;
    void visitVariable(const VariableNode& node) override;

    ValuePtr _result;
    Scope& _scope;
    Printer& _printer;
};
