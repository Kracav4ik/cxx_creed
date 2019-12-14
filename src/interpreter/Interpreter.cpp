#include "Interpreter.h"

#include "Evaluator.h"

#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/ParseErrorEvent.h"
#include "parser/events/ExprStmtEvent.h"
#include "parser/events/VarDeclEvent.h"
#include "parser/events/ReturnStmtEvent.h"
#include "parser/events/BeginIfStmtEvent.h"
#include "parser/events/BeginWhileStmtEvent.h"
#include "parser/EventVisitorAdapter.h"
#include "interpreter/types/ValueBase.h"
#include "interpreter/types/IntegerType.h"
#include "Printer.h"

#include <sstream>
#include <iostream>
#include <cassert>


struct IfBlockSkipper : public InterpreterBase, public EventVisitorAdapter {
    explicit IfBlockSkipper(ParserBase& parser) : InterpreterBase(parser) {}

    void visitBeginIfStmt(BeginIfStmtEvent& event) override {
        IfBlockSkipper skipper(get_parser());
        skipper.run();
    }

    void visitEndIfStmt(EndIfStmtEvent& event) override {
        _is_running = false;
    }
};

struct WhileBlockSkipper : public InterpreterBase, public EventVisitorAdapter {
    explicit WhileBlockSkipper(ParserBase& parser) : InterpreterBase(parser) {}

    void visitBeginWhileStmt(BeginWhileStmtEvent& event) override {
        WhileBlockSkipper skipper(get_parser());
        skipper.run();
    }

    void visitEndWhileStmt(EndWhileStmtEvent& event) override {
        _is_running = false;
    }
};

Interpreter::Interpreter(ParserBase& parser, Printer& printer)
    : InterpreterBase(parser), _printer(printer), _cachingParser(parser)
{
    _global_scope = std::make_shared<GlobalScope>();
    _scope = _global_scope;
    _global_scope->insert_type(IntegerType::get());
}

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
    s << ">>> return value `" << Evaluator::evaluate(event.value, *_scope, _printer)->printable_str() << "`";
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
        if (auto type = _scope->get_type(event.type_name)) {
            _scope->create_value(event.var_name, *type);
        } else {
            _printer.print_error("Unknown type " + event.type_name);
        }
    }
}

void Interpreter::visitBeginMainDecl(BeginMainDeclEvent& event) {
    push_scope();
}

void Interpreter::visitEndMainDecl(EndMainDeclEvent& event) {
    if (!_is_returning) {
        _printer.print_error("main() did not return a value");
    }
    _is_returning = false;
}

void Interpreter::visitBeginBlockStmt(BeginBlockStmtEvent& event) {
    push_scope();
}

void Interpreter::visitEndBlockStmt(EndBlockStmtEvent& event) {
    pop_scope();
}

void Interpreter::visitBeginIfStmt(BeginIfStmtEvent& event) {
    if (!_is_returning && Evaluator::evaluate(event.expr, *_scope, _printer)->is_true()) {
        push_scope();
    } else {
        IfBlockSkipper skipper(get_parser());
        skipper.run();
    }
}

void Interpreter::visitEndIfStmt(EndIfStmtEvent& event) {
    pop_scope();
}

void Interpreter::push_scope() {
    auto new_scope = std::make_shared<Scope>();
    new_scope->set_parent(_scope);
    _scope = new_scope;
}

void Interpreter::pop_scope() {
    _scope = _scope->get_parent();
    assert(_scope);
}

void Interpreter::visitBeginWhileStmt(BeginWhileStmtEvent& event) {
    if (!_is_returning && Evaluator::evaluate(event.expr, *_scope, _printer)->is_true()) {
        push_scope();
        _states.push_back(_cachingParser.state_before_event());
    } else {
        WhileBlockSkipper skipper(get_parser());
        skipper.run();
    }
}

void Interpreter::visitEndWhileStmt(EndWhileStmtEvent& event) {
    pop_scope();
    if (!_is_returning) {
        _states.back().revert();
    }
    _states.pop_back();
}

void Interpreter::visitInclude(IncludeEvent& event) {
    // TODO: implement includes
}

ParserBase& Interpreter::get_parser() {
    return _cachingParser;
}
