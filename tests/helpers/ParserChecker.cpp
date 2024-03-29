#include "ParserChecker.h"

#include "dlc/lexers/WhitespaceLexer.h"
#include "dlc/lexers/NewlineLexer.h"
#include "dlc/lexers/IdentifierLexer.h"
#include "dlc/lexers/IntegerLexer.h"
#include "dlc/lexers/StringLexer.h"
#include "dlc/lexers/LineCommentLexer.h"
#include "dlc/lexers/BlockCommentLexer.h"
#include "dlc/lexers/ExactLexer.h"
#include "dlc/lexers/IncludeLexer.h"

ParserChecker::ParserChecker(std::string text) : _parser(_lexer), _recorder(_parser) {
    // TODO: add from dlc description
    _lexer.add_dlc(std::make_shared<WhitespaceLexer>());
    _lexer.add_dlc(std::make_shared<NewlineLexer>());
    _lexer.add_dlc(std::make_shared<IdentifierLexer>());
    _lexer.add_dlc(std::make_shared<IntegerLexer>());
    _lexer.add_dlc(std::make_shared<StringLexer>());
    _lexer.add_dlc(std::make_shared<LineCommentLexer>());
    _lexer.add_dlc(std::make_shared<BlockCommentLexer>());
    _lexer.add_dlc(std::make_shared<IncludeLexer>());

    _lexer.add_dlc(std::make_shared<ExactLexer>("WHILE", "while"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("IF", "if"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("INT", "int"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("LPAR", "("));
    _lexer.add_dlc(std::make_shared<ExactLexer>("RPAR", ")"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("LBRACE", "{"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("RBRACE", "}"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("RETURN", "return"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("SEMICOLON", ";"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("ADD", "+"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("SUB", "-"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("MUL", "*"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("DIV", "/"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("MOD", "%"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("XOR", "^"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("BITAND", "&"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("BITOR", "|"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("COMPL", "~"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("LSHIFT", "<<"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("RSHIFT", ">>"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("ASSIGN", "="));
    _lexer.add_dlc(std::make_shared<ExactLexer>("EQ", "=="));
    _lexer.add_dlc(std::make_shared<ExactLexer>("NOTEQ", "!="));
    _lexer.add_dlc(std::make_shared<ExactLexer>("NOT", "!"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("LT", "<"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("LTEQ", "<="));
    _lexer.add_dlc(std::make_shared<ExactLexer>("GT", ">"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("GTEQ", ">="));
    _lexer.add_dlc(std::make_shared<ExactLexer>("OR", "||"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("AND", "&&"));


    _lexer.set_text(std::move(text));
    _recorder.run();
}

const Strings& ParserChecker::events() const {
    return _recorder.events();
}
