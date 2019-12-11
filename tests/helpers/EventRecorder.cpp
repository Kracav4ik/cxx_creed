#include "EventRecorder.h"

#include "parser/events/ParseErrorEvent.h"
#include "parser/events/ReturnStmtEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/ExprStmtEvent.h"
#include "parser/events/VarDeclEvent.h"
#include "parser/events/BeginIfStmtEvent.h"
#include "parser/events/BeginWhileStmtEvent.h"

#include "ASTNodeString.h"

EventRecorder::EventRecorder(ParserBase& parser) : InterpreterBase(parser) {
}

const Strings& EventRecorder::events() const {
    return _events;
}

void EventRecorder::visitUnknownToken(UnknownTokenEvent& event) {
    _events.emplace_back("UnknownToken " + event.token_text);
}

void EventRecorder::visitUnknownTokenType(UnknownTokenTypeEvent& event) {
    _events.emplace_back("UnknownTokenType " + event.token_type);
}

void EventRecorder::visitReturnStmt(ReturnStmtEvent& event) {
    _events.emplace_back("ReturnStmt " + ASTNodeString(event.value).str());
}

void EventRecorder::visitParseError(ParseErrorEvent& event) {
    _events.emplace_back("ParseError " + event.token.type + " " + event.token.text);
}

void EventRecorder::visitBeginMainDecl(BeginMainDeclEvent& event) {
    _events.emplace_back("BeginMainDecl");
}

void EventRecorder::visitEndMainDecl(EndMainDeclEvent& event) {
    _events.emplace_back("EndMainDecl");
}

void EventRecorder::visitExprStmt(ExprStmtEvent& event) {
    _events.emplace_back("ExprStmt " + ASTNodeString(event.expr).str());
}

void EventRecorder::visitVarDecl(VarDeclEvent& event) {
    _events.emplace_back("VarDecl " + event.var_name);
}

void EventRecorder::visitBeginBlockStmt(BeginBlockStmtEvent& event) {
    _events.emplace_back("BeginBlockStmt");
}

void EventRecorder::visitEndBlockStmt(EndBlockStmtEvent& event) {
    _events.emplace_back("EndBlockStmt");
}

void EventRecorder::visitBeginIfStmt(BeginIfStmtEvent& event) {
    _events.emplace_back("BeginIfStmt " + ASTNodeString(event.expr).str());
}

void EventRecorder::visitEndIfStmt(EndIfStmtEvent& event) {
    _events.emplace_back("EndIfStmt");
}

void EventRecorder::visitBeginWhileStmt(BeginWhileStmtEvent& event) {
    _events.emplace_back("BeginWhileStmt " + ASTNodeString(event.expr).str());
}

void EventRecorder::visitEndWhileStmt(EndWhileStmtEvent& event) {
    _events.emplace_back("EndWhileStmt");
}
