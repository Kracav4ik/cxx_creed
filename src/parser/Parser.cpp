#include "Parser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include "parser/events/EOFEvent.h"
#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/miniparsers/MainMiniparser.h"

Parser::Parser(Lexer& lexer) : _lexer(lexer) {
    _miniparser = std::make_unique<MainMiniparser>();
}

Parser::~Parser() = default;

std::shared_ptr<ASTEvent> Parser::next_event() {
    {
        auto state = _lexer.get_state();
        auto token = _lexer.next_token();
        if (token.type == "UNKNOWN") {
            state.drop();
            return std::make_shared<UnknownTokenEvent>(token.text);
        }
        if (token.type == "EOF") {
            state.drop();
            return std::make_shared<EOFEvent>();
        }
    }
    if (_miniparser) {
        if (auto event = _miniparser->try_next_event(_lexer)) {
            if (_miniparser->completed()) {
                _miniparser.reset();
            }
            return event;
        }
    }

    auto token = _lexer.next_token();
    return std::make_shared<UnknownTokenTypeEvent>(token.type);
}
