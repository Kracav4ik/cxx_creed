#pragma once

#include "dlc/ExpressionParserDLC.h"
#include "expression_parser/TokenList.h"

class BinaryOpParser : public ExpressionParserDLC {
public:
    BinaryOpParser(Priority priority, TokenList token_types);

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expression_parser) override;

private:
    TokenList _token_types;
};
