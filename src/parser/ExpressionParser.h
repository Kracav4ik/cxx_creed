#pragma once

#include "parser/ast/ASTNode.h"

class Lexer;

class ExpressionParser {
public:
    ASTNodePtr try_expression(Lexer& lexer);

private:
    ASTNodePtr try_inclusive_or_expression(Lexer& lexer);
    ASTNodePtr try_exclusive_or_expression(Lexer& lexer);
    ASTNodePtr try_and_expression(Lexer& lexer);
    ASTNodePtr try_shift_expression(Lexer& lexer);
    ASTNodePtr try_additive_expression(Lexer& lexer);
    ASTNodePtr try_multiplicative_expression(Lexer& lexer);
    ASTNodePtr try_unary_expression(Lexer& lexer);
    ASTNodePtr try_primary_expression(Lexer& lexer);
};
