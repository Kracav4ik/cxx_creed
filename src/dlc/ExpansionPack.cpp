#include "ExpansionPack.h"

#include "lexer/Lexer.h"

#include "dlc/lexers/WhitespaceLexer.h"
#include "dlc/lexers/NewlineLexer.h"
#include "dlc/lexers/IdentifierLexer.h"
#include "dlc/lexers/IntegerLexer.h"
#include "dlc/lexers/ExactLexer.h"

void ExpansionPack::install(Lexer& lexer, Parser& parser, Interpreter& interpreter) {
    lexer.add_dlc(std::make_shared<WhitespaceLexer>());
    lexer.add_dlc(std::make_shared<NewlineLexer>());
    lexer.add_dlc(std::make_shared<IdentifierLexer>());
    lexer.add_dlc(std::make_shared<IntegerLexer>());

    lexer.add_dlc(std::make_shared<ExactLexer>("INT", "int"));
    lexer.add_dlc(std::make_shared<ExactLexer>("LPAR", "("));
    lexer.add_dlc(std::make_shared<ExactLexer>("RPAR", ")"));
    lexer.add_dlc(std::make_shared<ExactLexer>("LBRACE", "{"));
    lexer.add_dlc(std::make_shared<ExactLexer>("RBRACE", "}"));
    lexer.add_dlc(std::make_shared<ExactLexer>("RETURN", "return"));
    lexer.add_dlc(std::make_shared<ExactLexer>("SEMICOLON", ";"));
}
