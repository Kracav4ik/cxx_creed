#include "StringParser.h"

#include "expression_parser/ExpressionParser.h"
#include "expression_parser/ast/StringNode.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"

StringParser::StringParser(Priority priority) : ExpressionParserDLC(priority) {}

ASTNodePtr StringParser::try_parse(Lexer& lexer, ExpressionParser& expression_parser) {
    auto state = lexer.get_state();
    if (auto token = lexer.next_token()) {
        if (token.type == "STRING") {
            state.drop();
            return std::make_unique<StringNode>(token.text);
        }
    }
    return nullptr;
}
