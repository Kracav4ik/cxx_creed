#include "Parser.h"

#include "parser/EOFEvent.h"
#include "parser/UnknownTokenEvent.h"
#include "parser/UnknownTokenTypeEvent.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"


Parser::Parser(Lexer& lexer)  : _lexer(lexer) {}

std::unique_ptr<ASTEvent> Parser::next_event() {
    auto token = _lexer.next_token();
    if (token.type == "UNKNOWN") {
        return std::make_unique<UnknownTokenEvent>(token.text);
    }
    if (token.type == "EOF") {
        return std::make_unique<EOFEvent>();
    }
    return std::make_unique<UnknownTokenTypeEvent>(token.type);
}
