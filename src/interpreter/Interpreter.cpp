#include "Interpreter.h"

#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/ParseErrorEvent.h"
#include "parser/events/ReturnStmtEvent.h"

#include <iostream>

Interpreter::Interpreter(Parser& parser)  : InterpreterBase(parser) {}

void Interpreter::visitUnknownToken(UnknownTokenEvent& event) {
    std::cerr << "unknown token: `" << event.token_text << "`" << std::endl;
}

void Interpreter::visitUnknownTokenType(UnknownTokenTypeEvent& event) {
    std::cerr << "unknown token type: " << event.token_type << std::endl;
}

void Interpreter::visitReturnStmt(ReturnStmtEvent& event) {
    std::cerr << ">>> return value `" << event.value << "`" << std::endl;
}

void Interpreter::visitParseError(ParseErrorEvent& event) {
    std::cerr << "parse error: token " << event.token.type << " `" << event.token.text << "`" << std::endl;
}
