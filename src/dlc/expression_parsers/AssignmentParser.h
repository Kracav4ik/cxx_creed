#pragma once

#include "dlc/ExpressionParserDLC.h"

class AssignmentParser : public ExpressionParserDLC {
public:
    explicit AssignmentParser(Priority priority);

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expression_parser) override;
};
