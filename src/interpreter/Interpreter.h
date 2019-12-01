#pragma once

#include "InterpreterBase.h"
#include "parser/EventVisitorAdapter.h"
#include "dlc/InterpreterDLC.h"
#include "dlc/WithDLC.h"
#include "Scope.h"

class Printer;

class Interpreter : public InterpreterBase, public WithDLC<InterpreterDLC>, public EventVisitorAdapter {
public:
    Interpreter(Parser& parser, Printer& printer);

private:
    void visitUnknownToken(UnknownTokenEvent& event) override;
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override;
    void visitExprStmt(ExprStmtEvent& event) override;
    void visitVarDecl(VarDeclEvent& event) override;

public:
    void visitEndMainDecl(EndMainDeclEvent& event) override;

private:
    void visitReturnStmt(ReturnStmtEvent& event) override;
    void visitParseError(ParseErrorEvent& event) override;

    bool _is_returning = false;
    Scope _scope;
    Printer& _printer;
};
