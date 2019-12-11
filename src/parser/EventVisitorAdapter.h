#pragma once

#include "EventVisitor.h"

class EventVisitorAdapter : virtual public EventVisitor {
public:
    void visitUnknownToken(UnknownTokenEvent& event) override {}
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override {}
    void visitExprStmt(ExprStmtEvent& event) override {}
    void visitVarDecl(VarDeclEvent& event) override {}
    void visitReturnStmt(ReturnStmtEvent& event) override {}
    void visitBeginIfDecl(BeginIfDeclEvent& event) override {}
    void visitEndIfDecl(EndIfDeclEvent& event) override {}
    void visitParseError(ParseErrorEvent& event) override {}
    void visitBeginMainDecl(BeginMainDeclEvent& event) override {}
    void visitEndMainDecl(EndMainDeclEvent& event) override {}
    void visitBeginBlockDecl(BeginBlockDeclEvent& event) override {}
    void visitEndBlockDecl(EndBlockDeclEvent& event) override {}
};
