#pragma once

#include "parser/ast/ASTNode.h"
#include <map>
#include <vector>

class Lexer;
class ExpressionParser;

enum class Priority {
    INCLUSIVE_OR_EXPRESSION,
    EXCLUSIVE_OR_EXPRESSION,
    AND_EXPRESSION,
    SHIFT_EXPRESSION,
    ADDITIVE_EXPRESSION,
    MULTIPLICATIVE_EXPRESSION,
    UNARY_EXPRESSION,
    PRIMARY_EXPRESSION,
};

class ExpressionParserDLC {
public:
    ExpressionParserDLC(Priority priority);

    virtual ~ExpressionParserDLC() = default;
    virtual ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expressionParser) = 0;
    Priority getPriority() const;

private:
    Priority _priority;
};

class ExpressionParser {
public:
    using DLC = ExpressionParserDLC;

    ExpressionParser();

    ASTNodePtr try_expression(Lexer& lexer);

    ASTNodePtr try_next_priority(Lexer& lexer, Priority priority);
    ASTNodePtr try_same_priority(Lexer& lexer, Priority priority);

    void add_dlc(std::shared_ptr<DLC> dlc);

private:
    using DlcMap = std::map<Priority, std::vector<std::shared_ptr<DLC>>>;

    ASTNodePtr try_parsers(Lexer& lexer, DlcMap::const_iterator parsers_it);

    DlcMap _dlc_map;
};
