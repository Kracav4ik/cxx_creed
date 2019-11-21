#include "Interpreter.h"

#include "parser/Parser.h"
#include "parser/EOFEvent.h"
#include "parser/UnknownTokenEvent.h"
#include "parser/UnknownTokenTypeEvent.h"

#include <iostream>

Interpreter::Interpreter(Parser& parser)  : _parser(parser) {}

void Interpreter::run() {
    _isRunning = true;
    while (_isRunning) {
        auto event = _parser.next_event();
        event->visit(*this);
    }
}

void Interpreter::visitUnknownToken(UnknownTokenEvent& event) {
    std::cerr << "unknown token: `" << event.token_text << "`" << std::endl;
}

void Interpreter::visitUnknownTokenType(UnknownTokenTypeEvent& event) {
    std::cerr << "unknown token type: " << event.token_type << std::endl;
}

void Interpreter::visitEOF(EOFEvent& event) {
    _isRunning = false;
}
