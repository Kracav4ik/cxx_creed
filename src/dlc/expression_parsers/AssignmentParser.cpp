#include "AssignmentParser.h"

#include "expression_parser/ExpressionParser.h"
#include "expression_parser/ast/AssignmentNode.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"

AssignmentParser::AssignmentParser(Priority priority) : ExpressionParserDLC(priority) {}

ASTNodePtr AssignmentParser::try_parse(Lexer& lexer, ExpressionParser& expression_parser) {
    auto first_operand = expression_parser.try_next_priority(lexer, getPriority());
    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();
        auto token = lexer.next_token();
        if (!token.valid() || token.type != "ASSIGN") {
            break;
        }

        auto second_operand = expression_parser.try_same_priority(lexer, getPriority());
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<AssignmentNode>(std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}
