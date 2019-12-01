#include "IntegerParser.h"

#include "expression_parser/ExpressionParser.h"
#include "expression_parser/ast/IntegerNode.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"

IntegerParser::IntegerParser(Priority priority) : ExpressionParserDLC(priority) {}

ASTNodePtr IntegerParser::try_parse(Lexer& lexer, ExpressionParser& expression_parser) {
    auto state = lexer.get_state();
    auto token = lexer.next_token();
    if (token.valid()) {
        if (token.type == "INTEGER") {
            state.drop();
            return std::make_unique<IntegerNode>((int)std::stoll(token.text));
        }
    }
    return nullptr;
}
