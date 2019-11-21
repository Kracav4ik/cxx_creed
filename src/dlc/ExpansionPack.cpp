#include "ExpansionPack.h"

#include "lexer/Lexer.h"

#include "dlc/lexers/WhitespaceLexer.h"

void ExpansionPack::install(Lexer& lexer, Parser& parser, Interpreter& interpreter) {
    lexer.add_dlc(std::make_shared<WhitespaceLexer>());
}
