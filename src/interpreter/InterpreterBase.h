#pragma once

#include "parser/EventVisitor.h"

class Parser;
class InterpreterBase : virtual public EventVisitor {
public:
    void run();

protected:
    explicit InterpreterBase(Parser& parser);

    void visitEOF(EOFEvent& event) override;

    bool _is_running = false;
    Parser& _parser;
};
