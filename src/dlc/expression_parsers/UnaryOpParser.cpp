#include "UnaryOpParser.h"

#include "expression_parser/ExpressionParser.h"
#include "expression_parser/ast/UnaryOpNode.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"

UnaryOpParser::UnaryOpParser(Priority priority, TokenList token_types) : ExpressionParserDLC(priority), _token_types(std::move(token_types)) {}

ASTNodePtr UnaryOpParser::try_parse(Lexer& lexer, ExpressionParser& expression_parser) {
    auto state = lexer.get_state();
    auto token = lexer.next_token();
    if (token.valid() && _token_types.has_token_type(token.type)) {
        auto expression = expression_parser.try_same_priority(lexer, getPriority());
        if (!expression) {
            return nullptr;
        }
        state.drop();
        return std::make_unique<UnaryOpNode>(token.type, token.text, std::move(expression));
    } else {
        state.revert();
        return expression_parser.try_next_priority(lexer, getPriority());
    }
}
