#include "IntegerParser.h"

#include "expression_parser/ExpressionParser.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/ast/IntegerNode.h"

IntegerParser::IntegerParser(Priority priority) : ExpressionParserDLC(priority) {}

ASTNodePtr IntegerParser::try_parse(Lexer& lexer, ExpressionParser& expressionParser) {
    auto state = lexer.get_state();
    auto token = lexer.next_token();
    if (token.valid()) {
        if (token.type == "INTEGER") {
            state.drop();
            return std::make_unique<IntegerNode>(std::stoi(token.text));
        }
    }
    return nullptr;
}
