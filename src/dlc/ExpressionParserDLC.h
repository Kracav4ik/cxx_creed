#pragma once

#include "parser/ast/ASTNode.h"
#include "expression_parser/Priority.h"

class Lexer;
class ExpressionParser;

class ExpressionParserDLC {
public:
    explicit ExpressionParserDLC(Priority priority);

    virtual ~ExpressionParserDLC() = default;
    virtual ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expression_parser) = 0;
    Priority getPriority() const;

private:
    Priority _priority;
};
