#include "Interpreter.h"

#include "parser/Parser.h"
#include "parser/EOFEvent.h"
#include "parser/UnknownTokenEvent.h"
#include "parser/UnknownTokenTypeEvent.h"
#include "parser/ParseErrorEvent.h"
#include "parser/ReturnStmtEvent.h"

#include <iostream>

Interpreter::Interpreter(Parser& parser)  : _parser(parser) {}

void Interpreter::run() {
    _is_running = true;
    while (_is_running) {
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
    _is_running = false;
}

void Interpreter::visitReturnStmt(ReturnStmtEvent& event) {
    std::cerr << "return value `" << event.value << "`" << std::endl;
}

void Interpreter::visitParseError(ParseErrorEvent& event) {
    std::cerr << "parse error: token " << event.token.type << " `" << event.token.text << "`" << std::endl;
}

void Interpreter::visitBeginMainDecl(BeginMainDeclEvent& event) {
}

void Interpreter::visitEndMainDecl(EndMainDeclEvent& event) {
}
