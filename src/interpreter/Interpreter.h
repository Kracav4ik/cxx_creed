#pragma once

#include "InterpreterBase.h"
#include "parser/EventVisitorAdapter.h"
#include "parser/CachingParser.h"
#include "dlc/InterpreterDLC.h"
#include "dlc/WithDLC.h"
#include "Scope.h"

class Printer;

class Interpreter : public InterpreterBase, public WithDLC<InterpreterDLC>, public EventVisitorAdapter {
public:
    Interpreter(ParserBase& parser, Printer& printer);

protected:
    ParserBase& get_parser() override;

private:
    void visitUnknownToken(UnknownTokenEvent& event) override;
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override;
    void visitExprStmt(ExprStmtEvent& event) override;
    void visitVarDecl(VarDeclEvent& event) override;
    void visitBeginIfDecl(BeginIfDeclEvent& event) override;
    void visitEndIfDecl(EndIfDeclEvent& event) override;
    void visitBeginMainDecl(BeginMainDeclEvent& event) override;
    void visitEndMainDecl(EndMainDeclEvent& event) override;
    void visitBeginBlockDecl(BeginBlockDeclEvent& event) override;
    void visitEndBlockDecl(EndBlockDeclEvent& event) override;
    void visitReturnStmt(ReturnStmtEvent& event) override;
    void visitParseError(ParseErrorEvent& event) override;
    void visitBeginWhileDecl(BeginWhileDeclEvent& event) override;
    void visitEndWhileDecl(EndWhileDeclEvent& event) override;

    bool _is_returning = false;
    std::shared_ptr<Scope> _scope;
    Printer& _printer;
    CachingParser _cachingParser;
    std::vector<CachingParser::State> _states;
};
