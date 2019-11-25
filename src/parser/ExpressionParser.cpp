#include "ExpressionParser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/ast/BinaryOpNode.h"
#include "parser/ast/UnaryOpNode.h"
#include "parser/ast/IntegerNode.h"

ASTNodePtr ExpressionParser::try_expression(Lexer& lexer) {
    return try_inclusive_or_expression(lexer);
}

ASTNodePtr ExpressionParser::try_inclusive_or_expression(Lexer& lexer) {
    auto first_operand = try_exclusive_or_expression(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "BITOR")) {
            break;
        }

        auto second_operand = try_exclusive_or_expression(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr ExpressionParser::try_exclusive_or_expression(Lexer& lexer) {
    auto first_operand = try_and_expression(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "XOR")) {
            break;
        }

        auto second_operand = try_and_expression(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr ExpressionParser::try_and_expression(Lexer& lexer) {
    auto first_operand = try_shift_expression(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "BITAND")) {
            break;
        }

        auto second_operand = try_shift_expression(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr ExpressionParser::try_shift_expression(Lexer& lexer) {
    auto first_operand = try_additive_expression(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "LSHIFT" || token.type == "RSHIFT")) {
            break;
        }

        auto second_operand = try_additive_expression(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
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
    auto first_operand = try_unary_expression(lexer);

    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();

        auto token = lexer.next_token();
        if (!token.valid() || !(token.type == "MUL" || token.type == "DIV" || token.type == "MOD")) {
            break;
        }

        auto second_operand = try_unary_expression(lexer);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr ExpressionParser::try_unary_expression(Lexer& lexer) {
    auto state = lexer.get_state();
    auto token = lexer.next_token();
    if (token.valid() && (token.type == "ADD" || token.type == "SUB" || token.type == "COMPL")) {
        auto expression = try_unary_expression(lexer);
        if (!expression) {
            return nullptr;
        }
        state.drop();
        return std::make_unique<UnaryOpNode>(token.text, std::move(expression));
    } else {
        state.revert();
        return try_primary_expression(lexer);
    }
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
            token = lexer.next_token();
            if (token.valid() && token.type == "RPAR") {
                state.drop();
                return expression;
            }
        }
    }
    return nullptr;
}
