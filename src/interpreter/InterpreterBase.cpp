#include "InterpreterBase.h"

#include "parser/Parser.h"
#include "parser/events/EOFEvent.h"

void InterpreterBase::run() {
    _is_running = true;
    while (_is_running) {
        auto event = get_parser().next_event();
        event->visit(*this);
    }
}

InterpreterBase::InterpreterBase(ParserBase& parser) : _parser(parser) {
}

void InterpreterBase::visitEOF(EOFEvent& event) {
    _is_running = false;
}

ParserBase& InterpreterBase::get_parser() {
    return _parser;
}
