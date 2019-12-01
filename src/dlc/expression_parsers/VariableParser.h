#pragma once

#include "dlc/ExpressionParserDLC.h"

class VariableParser : public ExpressionParserDLC {
public:
    explicit VariableParser(Priority priority);

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expression_parser) override;
};
