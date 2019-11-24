#include "ExpressionChecker.h"

#include "ASTNodeString.h"

#include "lexer/Lexer.h"
#include "dlc/lexers/WhitespaceLexer.h"
#include "dlc/lexers/IntegerLexer.h"
#include "dlc/lexers/ExactLexer.h"
#include "parser/ExpressionParser.h"

ExpressionChecker::ExpressionChecker(std::string expression) {
    Lexer lexer;
    // TODO: add from dlc description
    lexer.add_dlc(std::make_shared<WhitespaceLexer>());
    lexer.add_dlc(std::make_shared<IntegerLexer>());

    lexer.add_dlc(std::make_shared<ExactLexer>("ADD", "+"));
    lexer.add_dlc(std::make_shared<ExactLexer>("SUB", "-"));
    lexer.add_dlc(std::make_shared<ExactLexer>("MUL", "*"));
    lexer.add_dlc(std::make_shared<ExactLexer>("DIV", "/"));
    lexer.add_dlc(std::make_shared<ExactLexer>("MOD", "%"));

    lexer.set_text(std::move(expression));
    ExpressionParser expression_parser;
    auto node = expression_parser.try_expression(lexer);
    _str = ASTNodeString(node).str();
}

const std::string& ExpressionChecker::str() const {
    return _str;
}
