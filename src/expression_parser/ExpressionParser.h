#pragma once

#include "parser/ast/ASTNode.h"
#include "expression_parser/Priority.h"
#include <map>
#include <vector>

class Lexer;
class ExpressionParserDLC;

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
