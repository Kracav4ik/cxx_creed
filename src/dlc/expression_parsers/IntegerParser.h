#pragma once

#include "dlc/ExpressionParserDLC.h"

class IntegerParser : public ExpressionParserDLC {
public:
    explicit IntegerParser(Priority priority);

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expressionParser) override;
};
