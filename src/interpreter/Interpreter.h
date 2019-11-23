#pragma once

#include "InterpreterBase.h"
#include "parser/EventVisitorAdapter.h"
#include "dlc/InterpreterDLC.h"
#include "dlc/WithDLC.h"

class Interpreter : public InterpreterBase, public WithDLC<InterpreterDLC>, public EventVisitorAdapter {
public:
    explicit Interpreter(Parser& parser);

private:
    void visitUnknownToken(UnknownTokenEvent& event) override;
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override;
    void visitReturnStmt(ReturnStmtEvent& event) override;
    void visitParseError(ParseErrorEvent& event) override;
};
