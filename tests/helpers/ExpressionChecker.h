#pragma once

#include "expression_parser/ast/ASTNode.h"

#include <string>

class ExpressionChecker {
public:
    explicit ExpressionChecker(std::string expression);
    std::string str() const;
    int value() const;

private:
    ASTNodePtr _expression;
};
