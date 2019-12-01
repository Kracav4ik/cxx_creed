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
    virtual void visitBeginMainDecl(BeginMainDeclEvent& event) = 0;
    virtual void visitEndMainDecl(EndMainDeclEvent& event) = 0;
};
