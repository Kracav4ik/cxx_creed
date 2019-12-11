#pragma once

#include "interpreter/InterpreterBase.h"

#include "types.h"

class EventRecorder : public InterpreterBase {
public:
    explicit EventRecorder(ParserBase& parser);

    const Strings& events() const;

private:
    void visitUnknownToken(UnknownTokenEvent& event) override;
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override;
    void visitReturnStmt(ReturnStmtEvent& event) override;
    void visitParseError(ParseErrorEvent& event) override;
    void visitBeginIfDecl(BeginIfDeclEvent& event) override;
    void visitEndIfDecl(EndIfDeclEvent& event) override;
    void visitBeginMainDecl(BeginMainDeclEvent& event) override;
    void visitEndMainDecl(EndMainDeclEvent& event) override;
    void visitExprStmt(ExprStmtEvent& event) override;
    void visitVarDecl(VarDeclEvent& event) override;
    void visitBeginBlockDecl(BeginBlockDeclEvent& event) override;
    void visitEndBlockDecl(EndBlockDeclEvent& event) override;
    void visitBeginWhileDecl(BeginWhileDeclEvent& event) override;
    void visitEndWhileDecl(EndWhileDeclEvent& event) override;

    Strings _events;
};
