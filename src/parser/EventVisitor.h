#pragma once

struct UnknownTokenEvent;
struct UnknownTokenTypeEvent;
struct EOFEvent;
struct ExprStmtEvent;
struct VarDeclEvent;
struct ReturnStmtEvent;
struct ParseErrorEvent;
struct BeginMainDeclEvent;
struct EndMainDeclEvent;
struct BeginBlockStmtEvent;
struct EndBlockStmtEvent;
struct BeginIfStmtEvent;
struct EndIfStmtEvent;
struct BeginWhileStmtEvent;
struct EndWhileStmtEvent;

class EventVisitor {
public:
    virtual ~EventVisitor() = default;

    virtual void visitUnknownToken(UnknownTokenEvent& event) = 0;
    virtual void visitUnknownTokenType(UnknownTokenTypeEvent& event) = 0;
    virtual void visitEOF(EOFEvent& event) = 0;
    virtual void visitExprStmt(ExprStmtEvent& event) = 0;
    virtual void visitVarDecl(VarDeclEvent& event) = 0;
    virtual void visitReturnStmt(ReturnStmtEvent& event) = 0;
    virtual void visitParseError(ParseErrorEvent& event) = 0;
    virtual void visitBeginIfStmt(BeginIfStmtEvent& event) = 0;
    virtual void visitEndIfStmt(EndIfStmtEvent& event) = 0;
    virtual void visitBeginMainDecl(BeginMainDeclEvent& event) = 0;
    virtual void visitEndMainDecl(EndMainDeclEvent& event) = 0;
    virtual void visitBeginBlockStmt(BeginBlockStmtEvent& event) = 0;
    virtual void visitEndBlockStmt(EndBlockStmtEvent& event) = 0;
    virtual void visitBeginWhileStmt(BeginWhileStmtEvent& event) = 0;
    virtual void visitEndWhileStmt(EndWhileStmtEvent& event) = 0;
};
