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
    void visitReturnStmt(ReturnStmtEvent& event) override;
    void visitParseError(ParseErrorEvent& event) override;
    void visitBeginMainDecl(BeginMainDeclEvent& event) override;
    void visitEndMainDecl(EndMainDeclEvent& event) override;

    bool _isRunning = false;
    Parser& _parser;
};
