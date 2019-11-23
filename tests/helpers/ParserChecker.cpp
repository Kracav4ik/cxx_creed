#include "ParserChecker.h"

#include "dlc/lexers/WhitespaceLexer.h"
#include "dlc/lexers/IdentifierLexer.h"
#include "dlc/lexers/IntegerLexer.h"
#include "dlc/lexers/ExactLexer.h"

ParserChecker::ParserChecker(std::string text) : _parser(_lexer), _recorder(_parser) {
    // TODO: add from dlc description
    _lexer.add_dlc(std::make_shared<WhitespaceLexer>());
    _lexer.add_dlc(std::make_shared<IdentifierLexer>());
    _lexer.add_dlc(std::make_shared<IntegerLexer>());

    _lexer.add_dlc(std::make_shared<ExactLexer>("INT", "int"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("LPAR", "("));
    _lexer.add_dlc(std::make_shared<ExactLexer>("RPAR", ")"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("LBRACE", "{"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("RBRACE", "}"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("RETURN", "return"));
    _lexer.add_dlc(std::make_shared<ExactLexer>("SEMICOLON", ";"));

    _lexer.set_text(std::move(text));
    _recorder.run();
}

const Strings& ParserChecker::events() const {
    return _recorder.events();
}
