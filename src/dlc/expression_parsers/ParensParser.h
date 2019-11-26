#pragma once

#include "dlc/ExpressionParserDLC.h"

class ParensParser : public ExpressionParserDLC {
public:
    explicit ParensParser(Priority priority);

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expression_parser) override;
};
