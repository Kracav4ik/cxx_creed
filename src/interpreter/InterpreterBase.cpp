#include "InterpreterBase.h"

#include "parser/Parser.h"
#include "parser/EOFEvent.h"

void InterpreterBase::run() {
    _is_running = true;
    while (_is_running) {
        auto event = _parser.next_event();
        event->visit(*this);
    }
}

InterpreterBase::InterpreterBase(Parser& parser) : _parser(parser) {
}

void InterpreterBase::visitEOF(EOFEvent& event) {
    _is_running = false;
}
