#include "Evaluator.h"
#include "expression_parser/ast/BinaryOpNode.h"
#include "expression_parser/ast/UnaryOpNode.h"
#include "expression_parser/ast/IntegerNode.h"
#include "expression_parser/ast/AssignmentNode.h"
#include "expression_parser/ast/VariableNode.h"

#include "interpreter/types/IntegerType.h"
#include "interpreter/types/IntegerValue.h"

#include "Scope.h"
#include "Printer.h"

class NameGetter : ASTVisitor {
public:
    static std::string get_name(ASTNodePtr& node) {
        NameGetter getter;
        node->visit(getter);
        return getter._res;
    }

private:
    void visitBinaryOp(BinaryOpNode& node) override {}
    void visitUnaryOp(UnaryOpNode& node) override {}
    void visitInteger(IntegerNode& node) override {}
    void visitAssignment(AssignmentNode& node) override {}
    void visitVariable(VariableNode& node) override {
        _res = node.var_name;
    }
    std::string _res;
};

void check_value(int64_t val, Printer& printer) {
    if (val > std::numeric_limits<int>::max()) {
        printer.print_error("Integer overflow");
    }
    if (val < std::numeric_limits<int>::min()) {
        printer.print_error("Integer underflow");
    }
}

ValuePtr Evaluator::evaluate(const ASTNodePtr& node, Scope& scope, Printer& printer) {
    Evaluator evaluator(scope, printer);
    node->visit(evaluator);
    return evaluator._result;
}

void Evaluator::visitBinaryOp(BinaryOpNode& node) {
    auto first_op = evaluate(node.left, _scope, _printer);
    auto evaluate_second = [&node, this]() {
        return evaluate(node.right, _scope, _printer);
    }; 
    if (node.op == "||") {
        // TODO: don't hardcode type
        IntegerType type;
        if (first_op->is_true()) {
            _result = type.create_true();
            return;
        }
        _result = evaluate_second()->is_true() ? type.create_true() : type.create_false();
        return;
    } else if (node.op == "&&") {
        // TODO: don't hardcode type
        IntegerType type;
        if (!first_op->is_true()) {
            _result = type.create_false();
            return;
        }
        _result = evaluate_second()->is_true() ? type.create_true() : type.create_false();
        return;
    }
    auto second_op = evaluate_second();
    if (node.op == "+") {
        // TODO: check value
        _result = first_op->binary_add(second_op);
    } else if (node.op == "-") {
        // TODO: check value
        _result = first_op->binary_sub(second_op);
    } else if (node.op == "*") {
        // TODO: check value
        _result = first_op->binary_mul(second_op);
    } else if (node.op == "/") {
        // TODO: check value
        // TODO: check div by zero
        _result = first_op->binary_div(second_op);
    } else if (node.op == "%") {
        // TODO: check value
        // TODO: check div by zero
        _result = first_op->binary_mod(second_op);
    } else if (node.op == "^") {
        _result = first_op->binary_xor(second_op);
    } else if (node.op == "&") {
        _result = first_op->binary_bitand(second_op);
    } else if (node.op == "|") {
        _result = first_op->binary_bitor(second_op);
    } else if (node.op == "<<") {
        _result = first_op->binary_lshift(second_op);
    } else if (node.op == ">>") {
        _result = first_op->binary_rshift(second_op);
    } else if (node.op == "==") {
        _result = first_op->binary_eq(second_op);
    } else if (node.op == "!=") {
        _result = first_op->binary_noteq(second_op);
    } else if (node.op == "<") {
        _result = first_op->binary_lt(second_op);
    } else if (node.op == "<=") {
        _result = first_op->binary_lteq(second_op);
    } else if (node.op == ">") {
        _result = first_op->binary_gt(second_op);
    } else if (node.op == ">=") {
        _result = first_op->binary_gteq(second_op);
    } else {
        _printer.print_error("Unknown binary op " + node.op);
    }
}

void Evaluator::visitUnaryOp(UnaryOpNode& node) {
    auto operand = evaluate(node.subnode, _scope, _printer);
    if (node.op == "+") {
        _result = operand->unary_plus();
    } else if (node.op == "-") {
        // TODO: check value
        _result = operand->unary_minus();
    } else if (node.op == "~") {
        _result = operand->unary_compl();
    } else if (node.op == "!") {
        _result = operand->unary_not();
    } else {
        _printer.print_error("Unknown unary op " + node.op);
    }
}

void Evaluator::visitInteger(IntegerNode& node) {
    // TODO: get type from scope
    IntegerType type;
    _result = type.create_value(node.value);
}

void Evaluator::visitAssignment(AssignmentNode& node) {
    auto value = evaluate(node.right, _scope, _printer);
    _result = value;
    auto name = NameGetter::get_name(node.left);
    if (!_scope.has_name(name)) {
        if (name.empty()) {
            _printer.print_error("No variable to assign to");
        } else {
            _printer.print_error("Cannot assign to undeclared variable " + name);
        }
        return;
    }
    _scope.set_value(name, std::move(value));
}

void Evaluator::visitVariable(VariableNode& node) {
    if (!_scope.has_name(node.var_name)) {
        _printer.print_error("Unknown variable name " + node.var_name);
    }

    _result = _scope.get(node.var_name);
}

Evaluator::Evaluator(Scope& scope, Printer& printer) : _scope(scope), _printer(printer) {
    // TODO: don't hardcode type
    IntegerType type;
    _result = type.create_value();  // TODO: should be "undefined"
}
