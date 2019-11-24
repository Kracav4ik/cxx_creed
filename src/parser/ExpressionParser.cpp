#include "ExpressionParser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/ast/BinaryOpNode.h"
#include "parser/ast/IntegerNode.h"

ASTNodePtr ExpressionParser::try_expression(Lexer& lexer) {
    auto first_operand = try_term(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "ADD" || token.type == "SUB")) {
            break;
        }

        auto second_operand = try_term(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr ExpressionParser::try_term(Lexer& lexer) {
    // TODO: almost same code as try_expression
    auto first_operand = try_integer(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "MUL" || token.type == "DIV" || token.type == "MOD")) {
            break;
        }

        auto second_operand = try_integer(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr ExpressionParser::try_integer(Lexer& lexer) {
    auto state = lexer.get_state();
    auto token = lexer.next_token();
    if (token.valid() && token.type == "INTEGER") {
        state.drop();
        return std::make_unique<IntegerNode>(std::stoi(token.text));
    }
    return nullptr;
}
