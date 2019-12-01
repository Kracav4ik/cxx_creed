#pragma once

#include "expression_parser/ast/ASTNode.h"

#include <string>

class ExpressionParser;

class ExpressionChecker {
public:
    explicit ExpressionChecker(std::string expression);
    ExpressionChecker(std::string expression, ExpressionParser& expression_parser);
    std::string str() const;
    std::string str_messages() const;
    int value() const;

private:
    void make_ast(std::string&& expression, ExpressionParser& expression_parser);

    ASTNodePtr _expression;
};
