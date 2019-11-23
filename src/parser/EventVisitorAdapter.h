#pragma once

#include "EventVisitor.h"

class EventVisitorAdapter : virtual public EventVisitor {
public:
    void visitUnknownToken(UnknownTokenEvent& event) override {}
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override {}
    void visitReturnStmt(ReturnStmtEvent& event) override {}
    void visitParseError(ParseErrorEvent& event) override {}
    void visitBeginMainDecl(BeginMainDeclEvent& event) override {}
    void visitEndMainDecl(EndMainDeclEvent& event) override {}
};
