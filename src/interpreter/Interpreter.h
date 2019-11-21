#pragma once

#include "parser/EventVisitor.h"
#include "dlc/InterpreterDLC.h"
#include "dlc/WithDLC.h"

class Parser;

class Interpreter : public WithDLC<InterpreterDLC>, EventVisitor {
public:
    explicit Interpreter(Parser& parser);

    void run();

private:
    void visitUnknownToken(UnknownTokenEvent& event) override;
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override;
    void visitEOF(EOFEvent& event) override;

    bool _isRunning = false;
    Parser& _parser;
};
