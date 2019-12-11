#pragma once

#include "parser/EventVisitor.h"

class ParserBase;
class InterpreterBase : virtual public EventVisitor {
public:
    void run();

protected:
    explicit InterpreterBase(ParserBase& parser);

    void visitEOF(EOFEvent& event) override;
    virtual ParserBase& get_parser();

    bool _is_running = false;

private:
    ParserBase& _parser;
};
