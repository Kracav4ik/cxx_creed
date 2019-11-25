#include "ExpressionChecker.h"

#include "ASTNodeString.h"

#include "lexer/Lexer.h"
#include "dlc/lexers/WhitespaceLexer.h"
#include "dlc/lexers/IntegerLexer.h"
#include "dlc/lexers/ExactLexer.h"
#include "parser/ExpressionParser.h"
#include "interpreter/Evaluator.h"

ExpressionChecker::ExpressionChecker(std::string expression) {
    Lexer lexer;
    // TODO: add from dlc description
    lexer.add_dlc(std::make_shared<WhitespaceLexer>());
    lexer.add_dlc(std::make_shared<IntegerLexer>());

    lexer.add_dlc(std::make_shared<ExactLexer>("LPAR", "("));
    lexer.add_dlc(std::make_shared<ExactLexer>("RPAR", ")"));
    lexer.add_dlc(std::make_shared<ExactLexer>("ADD", "+"));
    lexer.add_dlc(std::make_shared<ExactLexer>("SUB", "-"));
    lexer.add_dlc(std::make_shared<ExactLexer>("MUL", "*"));
    lexer.add_dlc(std::make_shared<ExactLexer>("DIV", "/"));
    lexer.add_dlc(std::make_shared<ExactLexer>("MOD", "%"));
    lexer.add_dlc(std::make_shared<ExactLexer>("XOR", "^"));
    lexer.add_dlc(std::make_shared<ExactLexer>("BITAND", "&"));
    lexer.add_dlc(std::make_shared<ExactLexer>("BITOR", "|"));
    lexer.add_dlc(std::make_shared<ExactLexer>("COMPL", "~"));
    lexer.add_dlc(std::make_shared<ExactLexer>("LSHIFT", "<<"));
    lexer.add_dlc(std::make_shared<ExactLexer>("RSHIFT", ">>"));

    lexer.set_text(std::move(expression));
    ExpressionParser expression_parser;
    _expression = expression_parser.try_expression(lexer);
}

std::string ExpressionChecker::str() const {
    return ASTNodeString(_expression).str();
}

int ExpressionChecker::value() const {
    if (_expression) {
        return Evaluator::evaluate(_expression);
    }
    return 0;
}
