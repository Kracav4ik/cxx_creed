#pragma once

#include "InterpreterBase.h"
#include "parser/CachingParser.h"
#include "dlc/InterpreterDLC.h"
#include "dlc/WithDLC.h"
#include "Scope.h"
#include "GlobalScope.h"

class Printer;

class Interpreter : public InterpreterBase, public WithDLC<InterpreterDLC> {
public:
    Interpreter(ParserBase& parser, Printer& printer);

protected:
    ParserBase& get_parser() override;

private:
    void pop_scope();
    void push_scope();
    void visitUnknownToken(UnknownTokenEvent& event) override;
    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override;
    void visitExprStmt(ExprStmtEvent& event) override;
    void visitVarDecl(VarDeclEvent& event) override;
    void visitBeginIfStmt(BeginIfStmtEvent& event) override;
    void visitEndIfStmt(EndIfStmtEvent& event) override;
    void visitBeginMainDecl(BeginMainDeclEvent& event) override;
    void visitEndMainDecl(EndMainDeclEvent& event) override;
    void visitBeginBlockStmt(BeginBlockStmtEvent& event) override;
    void visitEndBlockStmt(EndBlockStmtEvent& event) override;
    void visitReturnStmt(ReturnStmtEvent& event) override;
    void visitParseError(ParseErrorEvent& event) override;
    void visitBeginWhileStmt(BeginWhileStmtEvent& event) override;
    void visitEndWhileStmt(EndWhileStmtEvent& event) override;
    void visitInclude(IncludeEvent& event) override;

    bool _is_returning = false;
    std::shared_ptr<Scope> _scope;
    std::shared_ptr<GlobalScope> _global_scope;
    Printer& _printer;
    CachingParser _cachingParser;
    std::vector<CachingParser::State> _states;
};
