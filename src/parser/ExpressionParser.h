#pragma once

#include "parser/ast/ASTNode.h"

class Lexer;

class ExpressionParser {
public:
    ASTNodePtr try_expression(Lexer& lexer);

private:
    ASTNodePtr try_term(Lexer& lexer);
    ASTNodePtr try_integer(Lexer& lexer);
};
