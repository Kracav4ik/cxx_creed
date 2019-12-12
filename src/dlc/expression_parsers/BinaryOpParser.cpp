#include "BinaryOpParser.h"

#include "expression_parser/ExpressionParser.h"
#include "expression_parser/ast/BinaryOpNode.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"

BinaryOpParser::BinaryOpParser(Priority priority, TokenList token_types) : ExpressionParserDLC(priority), _token_types(std::move(token_types)) {}

ASTNodePtr BinaryOpParser::try_parse(Lexer& lexer, ExpressionParser& expression_parser) {
    auto first_operand = expression_parser.try_next_priority(lexer, getPriority());
    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();
        auto token = lexer.next_token();
        if (!token.valid() || !_token_types.has_token_type(token.type)) {
            break;
        }

        auto second_operand = expression_parser.try_next_priority(lexer, getPriority());
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.type, token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}
