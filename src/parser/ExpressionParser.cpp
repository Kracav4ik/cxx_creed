#include "ExpressionParser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/ast/BinaryOpNode.h"
#include "parser/ast/IntegerNode.h"

ASTNodePtr ExpressionParser::try_expression(Lexer& lexer) {
    return try_additive_expression(lexer);
}

ASTNodePtr ExpressionParser::try_additive_expression(Lexer& lexer) {
    auto first_operand = try_multiplicative_expression(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "ADD" || token.type == "SUB")) {
            break;
        }

        auto second_operand = try_multiplicative_expression(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr ExpressionParser::try_multiplicative_expression(Lexer& lexer) {
    // TODO: almost same code as try_expression
    auto first_operand = try_primary_expression(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "MUL" || token.type == "DIV" || token.type == "MOD")) {
            break;
        }

        auto second_operand = try_primary_expression(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr ExpressionParser::try_primary_expression(Lexer& lexer) {
    auto state = lexer.get_state();
    auto token = lexer.next_token();
    if (token.valid()) {
        if (token.type == "INTEGER") {
            state.drop();
            return std::make_unique<IntegerNode>(std::stoi(token.text));
        }
        if (token.type == "LPAR") {
            auto expression = try_expression(lexer);
            if (!expression) {
                return nullptr;
            }
            auto inner_state = lexer.get_state();
            token = lexer.next_token();
            if (token.valid() && token.type == "RPAR") {
                inner_state.drop();
                return expression;
            }
        }
    }
    return nullptr;
}
