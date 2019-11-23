#include "Evaluator.h"
#include "parser/ast/BinaryOpNode.h"
#include "parser/ast/IntegerNode.h"

int Evaluator::evaluate(const ASTNodePtr& node) {
    Evaluator evaluator;
    node->visit(evaluator);
    return evaluator._result;
}

void Evaluator::visitBinaryOp(BinaryOpNode& node) {
    if (node.op == "+") {
        _result = evaluate(node.left) + evaluate(node.right);
    } else if (node.op == "-") {
        _result = evaluate(node.left) - evaluate(node.right);
    }
}

void Evaluator::visitInteger(IntegerNode& node) {
    _result = node.value;
}
