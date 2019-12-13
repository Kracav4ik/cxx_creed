#pragma once

#include "dlc/ExpressionParserDLC.h"

class StringParser : public ExpressionParserDLC {
public:
    explicit StringParser(Priority priority);

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expression_parser) override;
};
