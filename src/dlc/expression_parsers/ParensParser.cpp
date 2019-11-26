#include "ParensParser.h"

#include "expression_parser/ExpressionParser.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"

ParensParser::ParensParser(Priority priority) : ExpressionParserDLC(priority) {}

ASTNodePtr ParensParser::try_parse(Lexer& lexer, ExpressionParser& expression_parser) {
    auto state = lexer.get_state();
    auto token = lexer.next_token();
    if (token.valid()) {
        if (token.type == "LPAR") {
            auto expression = expression_parser.try_expression(lexer);
            if (!expression) {
                return nullptr;
            }
            token = lexer.next_token();
            if (token.valid() && token.type == "RPAR") {
                state.drop();
                return expression;
            }
        }
    }
    return nullptr;
}
