#include "Evaluator.h"
#include "expression_parser/ast/BinaryOpNode.h"
#include "expression_parser/ast/UnaryOpNode.h"
#include "expression_parser/ast/IntegerNode.h"
#include "expression_parser/ast/AssignmentNode.h"
#include "expression_parser/ast/VariableNode.h"
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

int Evaluator::evaluate(const ASTNodePtr& node, Scope& scope, Printer& printer) {
    Evaluator evaluator(scope, printer);
    node->visit(evaluator);
    return evaluator._result;
}

namespace {
const int FALSE_VALUE = 0;
const int TRUE_VALUE = 1;

int bool_convert(bool val) {
    return val ? TRUE_VALUE : FALSE_VALUE;
}
int bool_convert(int val) {
    return bool_convert(Evaluator::is_true(val));
}
}

bool Evaluator::is_true(int val) {
    return val != FALSE_VALUE;
}

void Evaluator::visitBinaryOp(BinaryOpNode& node) {
    int first_op = evaluate(node.left, _scope, _printer);
    auto evaluate_second = [&node, this]() {
        return evaluate(node.right, _scope, _printer);
    }; 
    if (node.op == "||") {
        if (is_true(first_op)) {
            _result = TRUE_VALUE;
            return;
        }
        _result = bool_convert(evaluate_second());
        return;
    } else if (node.op == "&&") {
        if (!is_true(first_op)) {
            _result = FALSE_VALUE;
            return;
        }
        _result = bool_convert(evaluate_second());
        return;
    }
    int second_op = evaluate_second();
    if (node.op == "+") {
        int64_t to_check = (int64_t)first_op + (int64_t)second_op;
        check_value(to_check, _printer);
        _result = to_check;
    } else if (node.op == "-") {
        int64_t to_check = (int64_t)first_op - (int64_t)second_op;
        check_value(to_check, _printer);
        _result = to_check;
    } else if (node.op == "*") {
        int64_t to_check = (int64_t)first_op * (int64_t)second_op;
        check_value(to_check, _printer);
        _result = to_check;
    } else if (node.op == "/") {
        if (second_op == 0) {
            _result = 0;
            _printer.print_error("Integer division by zero");
            return;
        }
        int64_t to_check = (int64_t)first_op / (int64_t)second_op;
        check_value(to_check, _printer);
        _result = to_check;
    } else if (node.op == "%") {
        if (second_op == 0) {
            _result = 0;
            _printer.print_error("Remainder of integer division by zero");
            return;
        }
        _result = first_op % second_op;
    } else if (node.op == "^") {
        _result = first_op ^ second_op;
    } else if (node.op == "&") {
        _result = first_op & second_op;
    } else if (node.op == "|") {
        _result = first_op | second_op;
    } else if (node.op == "<<") {
        _result = first_op << second_op;
    } else if (node.op == ">>") {
        _result = first_op >> second_op;
    } else if (node.op == "==") {
        _result = bool_convert(first_op == second_op);
    } else if (node.op == "!=") {
        _result = bool_convert(first_op != second_op);
    } else if (node.op == "<") {
        _result = bool_convert(first_op < second_op);
    } else if (node.op == "<=") {
        _result = bool_convert(first_op <= second_op);
    } else if (node.op == ">") {
        _result = bool_convert(first_op > second_op);
    } else if (node.op == ">=") {
        _result = bool_convert(first_op >= second_op);
    } else {
        _printer.print_error("Unknown binary op " + node.op);
    }
}

void Evaluator::visitUnaryOp(UnaryOpNode& node) {
    int operand = evaluate(node.subnode, _scope, _printer);
    if (node.op == "+") {
        _result = operand;
    } else if (node.op == "-") {
        int64_t to_check = -(int64_t)operand;
        check_value(to_check, _printer);
        _result = to_check;
    } else if (node.op == "~") {
        _result = ~operand;
    } else if (node.op == "!") {
        _result = bool_convert(!is_true(operand));
    } else {
        _printer.print_error("Unknown unary op " + node.op);
    }
}

void Evaluator::visitInteger(IntegerNode& node) {
    _result = node.value;
}

void Evaluator::visitAssignment(AssignmentNode& node) {
    int value = evaluate(node.right, _scope, _printer);
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
    _scope.set_value(name, value);
}

void Evaluator::visitVariable(VariableNode& node) {
    if (!_scope.has_name(node.var_name)) {
        _printer.print_error("Unknown variable name " + node.var_name);
    }

    _result = _scope.get(node.var_name);
}

Evaluator::Evaluator(Scope& scope, Printer& printer) : _scope(scope), _printer(printer) {}
