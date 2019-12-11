#include "ExpressionChecker.h"

#include "ASTNodeString.h"

#include "lexer/Lexer.h"
#include "dlc/lexers/WhitespaceLexer.h"
#include "dlc/lexers/IntegerLexer.h"
#include "dlc/lexers/ExactLexer.h"
#include "dlc/lexers/IdentifierLexer.h"
#include "expression_parser/ExpressionParser.h"
#include "interpreter/Evaluator.h"
#include "interpreter/Scope.h"
#include "interpreter/types/IntegerValue.h"

#include "TestPrinter.h"

ExpressionChecker::ExpressionChecker(std::string expression) {
    ExpressionParser expression_parser;
    make_ast(std::move(expression), expression_parser);
}

ExpressionChecker::ExpressionChecker(std::string expression, ExpressionParser& expression_parser) {
    make_ast(std::move(expression), expression_parser);
}

void ExpressionChecker::make_ast(std::string&& expression, ExpressionParser& expression_parser) {
    Lexer lexer;
    // TODO: add from dlc description
    lexer.add_dlc(std::make_shared<WhitespaceLexer>());
    lexer.add_dlc(std::make_shared<IntegerLexer>());
    lexer.add_dlc(std::make_shared<IdentifierLexer>());

    lexer.add_dlc(std::make_shared<ExactLexer>("LPAR", "("));
    lexer.add_dlc(std::make_shared<ExactLexer>("RPAR", ")"));
    lexer.add_dlc(std::make_shared<ExactLexer>("SEMICOLON", ";"));
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
    lexer.add_dlc(std::make_shared<ExactLexer>("ASSIGN", "="));
    lexer.add_dlc(std::make_shared<ExactLexer>("EQ", "=="));
    lexer.add_dlc(std::make_shared<ExactLexer>("NOTEQ", "!="));
    lexer.add_dlc(std::make_shared<ExactLexer>("NOT", "!"));
    lexer.add_dlc(std::make_shared<ExactLexer>("LT", "<"));
    lexer.add_dlc(std::make_shared<ExactLexer>("LTEQ", "<="));
    lexer.add_dlc(std::make_shared<ExactLexer>("GT", ">"));
    lexer.add_dlc(std::make_shared<ExactLexer>("GTEQ", ">="));
    lexer.add_dlc(std::make_shared<ExactLexer>("OR", "||"));
    lexer.add_dlc(std::make_shared<ExactLexer>("AND", "&&"));

    lexer.set_text(std::move(expression));
    _expression = expression_parser.try_expression(lexer);
}

std::string ExpressionChecker::str() const {
    return ASTNodeString(_expression).str();
}

int ExpressionChecker::value() const {
    if (_expression) {
        Scope scope;
        TestPrinter printer;
        auto value = Evaluator::evaluate(_expression, scope, printer);
        if (auto int_value = std::dynamic_pointer_cast<IntegerValue>(value)) {
            return int_value->get_value();
        }
    }
    return 0;
}

std::string ExpressionChecker::str_messages() const {
    if (_expression) {
        Scope scope;
        TestPrinter printer;
        Evaluator::evaluate(_expression, scope, printer);
        return printer.str();
    }
    return "";
}
