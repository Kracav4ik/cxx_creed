#pragma once

struct UnknownTokenEvent;
struct UnknownTokenTypeEvent;
struct EOFEvent;
struct ReturnStmtEvent;
struct ParseErrorEvent;
struct BeginMainDeclEvent;
struct EndMainDeclEvent;

class EventVisitor {
public:
    virtual ~EventVisitor() = default;

    virtual void visitUnknownToken(UnknownTokenEvent& event) {}
    virtual void visitUnknownTokenType(UnknownTokenTypeEvent& event) {}
    virtual void visitEOF(EOFEvent& event) {}
    virtual void visitReturnStmt(ReturnStmtEvent& event) {}
    virtual void visitParseError(ParseErrorEvent& event) {}
    virtual void visitBeginMainDecl(BeginMainDeclEvent& event) {}
    virtual void visitEndMainDecl(EndMainDeclEvent& event) {}
};
