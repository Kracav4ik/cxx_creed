#include "Interpreter.h"

#include "Evaluator.h"

#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/ParseErrorEvent.h"
#include "parser/events/ExprStmtEvent.h"
#include "parser/events/VarDeclEvent.h"
#include "parser/events/ReturnStmtEvent.h"
#include "Printer.h"

#include <sstream>
#include <iostream>

Interpreter::Interpreter(Parser& parser, Printer& printer) : InterpreterBase(parser), _printer(printer) {}

void Interpreter::visitUnknownToken(UnknownTokenEvent& event) {
    std::stringstream s;
    s << "Unknown token: `" << event.token_text << "`";
    _printer.print_error(s.str());
}

void Interpreter::visitUnknownTokenType(UnknownTokenTypeEvent& event) {
    std::stringstream s;
    s << "Unknown token type: " << event.token_type;
    _printer.print_error(s.str());
}

void Interpreter::visitReturnStmt(ReturnStmtEvent& event) {
    if (_is_returning) {
        return;
    }
    std::stringstream s;
    s << ">>> return value `" << Evaluator::evaluate(event.value, _scope, _printer) << "`";
    _printer.print_message(s.str());
    _is_returning = true;
}

void Interpreter::visitParseError(ParseErrorEvent& event) {
    std::stringstream s;
    s << "Parse error: token " << event.token.type << " `" << event.token.text << "`";
    _printer.print_error(s.str());
}

void Interpreter::visitExprStmt(ExprStmtEvent& event) {
    if (_is_returning) {
        return;
    }
    Evaluator::evaluate(event.expr, _scope, _printer);
}

void Interpreter::visitVarDecl(VarDeclEvent& event) {
    if (_is_returning) {
        return;
    }
    if (_scope.has_name(event.var_name)) {
        _printer.print_error("Variable " + event.var_name + " already declared");
    } else {
        _scope.set(event.var_name, 0);
    }
}

void Interpreter::visitEndMainDecl(EndMainDeclEvent& event) {
    if (!_is_returning) {
        _printer.print_error("main() did not return a value");
    }
    _is_returning = false;
}
