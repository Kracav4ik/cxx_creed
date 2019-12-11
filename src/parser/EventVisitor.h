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
struct BeginBlockDeclEvent;
struct EndBlockDeclEvent;
struct BeginIfDeclEvent;
struct EndIfDeclEvent;
struct BeginWhileDeclEvent;
struct EndWhileDeclEvent;

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
    virtual void visitBeginIfDecl(BeginIfDeclEvent& event) = 0;
    virtual void visitEndIfDecl(EndIfDeclEvent& event) = 0;
    virtual void visitBeginMainDecl(BeginMainDeclEvent& event) = 0;
    virtual void visitEndMainDecl(EndMainDeclEvent& event) = 0;
    virtual void visitBeginBlockDecl(BeginBlockDeclEvent& event) = 0;
    virtual void visitEndBlockDecl(EndBlockDeclEvent& event) = 0;
    virtual void visitBeginWhileDecl(BeginWhileDeclEvent& event) = 0;
    virtual void visitEndWhileDecl(EndWhileDeclEvent& event) = 0;
};
