#include "Parser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include "parser/events/EOFEvent.h"
#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/BeginMainDeclEvent.h"
#include "parser/miniparsers/MainMiniparser.h"

Parser::Parser(Lexer& lexer) : _lexer(lexer) {
}

Parser::~Parser() = default;

std::unique_ptr<ASTEvent> Parser::try_eat_begin_main() {
    auto state = _lexer.get_state();
    for (auto token_type : {"INT", "IDENTIFIER", "LPAR", "RPAR", "LBRACE"}) {
        auto token = _lexer.next_token_with_type(token_type);
        if (!token.valid() || (token.type == "IDENTIFIER" && token.text != "main")) {
            return nullptr;
        }
    }
    state.drop();
    return std::make_unique<BeginMainDeclEvent>();  // TODO: should be in MainMiniparser
}

std::unique_ptr<ASTEvent> Parser::next_event() {
    {
        auto state = _lexer.get_state();
        auto token = _lexer.next_token();
        if (token.type == "UNKNOWN") {
            state.drop();
            return std::make_unique<UnknownTokenEvent>(token.text);
        }
        if (token.type == "EOF") {
            state.drop();
            return std::make_unique<EOFEvent>();
        }
    }

    if (!_miniparser) {
        if (auto event = try_eat_begin_main()) {
            _miniparser = std::make_unique<MainMiniparser>();
            return event;
        }
    } else {
        if (auto event = _miniparser->try_next_event(_lexer)) {
            if (_miniparser->completed()) {
                _miniparser.reset();
            }
            return event;
        }
    }

    auto token = _lexer.next_token();
    return std::make_unique<UnknownTokenTypeEvent>(token.type);
}
