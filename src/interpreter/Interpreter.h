#pragma once

#include "parser/EventVisitorAdapter.h"
#include "dlc/InterpreterDLC.h"
#include "dlc/WithDLC.h"

class Parser;

class Interpreter : public WithDLC<InterpreterDLC>, EventVisitorAdapter {
public:
    explicit Interpreter(Parser& parser);

    void run();

private:
    void visitUnknownToken(UnknownTokenEvent& event) override;
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override;
    void visitEOF(EOFEvent& event) override;
    void visitReturnStmt(ReturnStmtEvent& event) override;
    void visitParseError(ParseErrorEvent& event) override;
    void visitBeginMainDecl(BeginMainDeclEvent& event) override;
    void visitEndMainDecl(EndMainDeclEvent& event) override;

    bool _is_running = false;
    Parser& _parser;
};
