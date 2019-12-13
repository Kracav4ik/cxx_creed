#pragma once

#include "EventVisitor.h"

class EventVisitorAdapter : virtual public EventVisitor {
public:
    void visitUnknownToken(UnknownTokenEvent& event) override {}
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override {}
    void visitExprStmt(ExprStmtEvent& event) override {}
    void visitVarDecl(VarDeclEvent& event) override {}
    void visitReturnStmt(ReturnStmtEvent& event) override {}
    void visitBeginIfStmt(BeginIfStmtEvent& event) override {}
    void visitEndIfStmt(EndIfStmtEvent& event) override {}
    void visitParseError(ParseErrorEvent& event) override {}
    void visitBeginMainDecl(BeginMainDeclEvent& event) override {}
    void visitEndMainDecl(EndMainDeclEvent& event) override {}
    void visitBeginBlockStmt(BeginBlockStmtEvent& event) override {}
    void visitEndBlockStmt(EndBlockStmtEvent& event) override {}
    void visitBeginWhileStmt(BeginWhileStmtEvent& event) override {}
    void visitEndWhileStmt(EndWhileStmtEvent& event) override {}
    void visitInclude(IncludeEvent& event) override {}
};
