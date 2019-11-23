#include "Interpreter.h"

#include "parser/UnknownTokenEvent.h"
#include "parser/UnknownTokenTypeEvent.h"
#include "parser/ParseErrorEvent.h"
#include "parser/ReturnStmtEvent.h"

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
