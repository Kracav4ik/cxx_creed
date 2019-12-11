#include "Interpreter.h"

#include "Evaluator.h"

#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/ParseErrorEvent.h"
#include "parser/events/ExprStmtEvent.h"
#include "parser/events/VarDeclEvent.h"
#include "parser/events/ReturnStmtEvent.h"
#include "parser/events/BeginIfDeclEvent.h"
#include "Printer.h"

#include <sstream>
#include <iostream>


struct IfBlockSkipper : public InterpreterBase, public EventVisitorAdapter {
    explicit IfBlockSkipper(Parser& parser) : InterpreterBase(parser) {}

    void visitBeginIfDecl(BeginIfDeclEvent& event) override {
        IfBlockSkipper skipper(_parser);
        skipper.run();
    }

    void visitEndIfDecl(EndIfDeclEvent& event) override {
        _is_running = false;
    }
};


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
    if (_is_returning || !_scope) {
        return;
    }
    std::stringstream s;
    s << ">>> return value `" << Evaluator::evaluate(event.value, *_scope, _printer) << "`";
    _printer.print_message(s.str());
    _is_returning = true;
}

void Interpreter::visitParseError(ParseErrorEvent& event) {
    std::stringstream s;
    s << "Parse error: token " << event.token.type << " `" << event.token.text << "`";
    _printer.print_error(s.str());
}

void Interpreter::visitExprStmt(ExprStmtEvent& event) {
    if (_is_returning || !_scope) {
        return;
    }
    Evaluator::evaluate(event.expr, *_scope, _printer);
}

void Interpreter::visitVarDecl(VarDeclEvent& event) {
    if (_is_returning || !_scope) {
        return;
    }
    if (_scope->has_name_local(event.var_name)) {
        _printer.print_error("Variable " + event.var_name + " already declared");
    } else {
        _scope->create_value(event.var_name);
    }
}

void Interpreter::visitBeginMainDecl(BeginMainDeclEvent& event) {
    _scope = std::make_shared<Scope>();
}

void Interpreter::visitEndMainDecl(EndMainDeclEvent& event) {
    if (!_is_returning) {
        _printer.print_error("main() did not return a value");
    }
    _is_returning = false;
}

void Interpreter::visitBeginBlockDecl(BeginBlockDeclEvent& event) {
    auto new_scope = std::make_shared<Scope>();
    new_scope->set_parent(_scope);
    _scope = new_scope;
}

void Interpreter::visitEndBlockDecl(EndBlockDeclEvent& event) {
    _scope = _scope->get_parent();
}

void Interpreter::visitBeginIfDecl(BeginIfDeclEvent& event) {
    if (Evaluator::is_true(Evaluator::evaluate(event.expr, *_scope, _printer))) {
        auto new_scope = std::make_shared<Scope>();
        new_scope->set_parent(_scope);
        _scope = new_scope;
    } else {
        IfBlockSkipper skipper(_parser);
        skipper.run();
    }
}

void Interpreter::visitEndIfDecl(EndIfDeclEvent& event) {
    _scope = _scope->get_parent();
}
