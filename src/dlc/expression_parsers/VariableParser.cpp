#include "VariableParser.h"

#include "expression_parser/ExpressionParser.h"
#include "expression_parser/ast/VariableNode.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"

VariableParser::VariableParser(Priority priority) : ExpressionParserDLC(priority) {}

ASTNodePtr VariableParser::try_parse(Lexer& lexer, ExpressionParser& expression_parser) {
    auto state = lexer.get_state();
    if (auto token = lexer.next_token()) {
        if (token.type == "IDENTIFIER") {
            state.drop();
            return std::make_unique<VariableNode>(token.text);
        }
    }
    return nullptr;
}
