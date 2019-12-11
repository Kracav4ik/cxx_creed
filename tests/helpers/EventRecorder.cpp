#include "EventRecorder.h"

#include "parser/events/ParseErrorEvent.h"
#include "parser/events/ReturnStmtEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/ExprStmtEvent.h"
#include "parser/events/VarDeclEvent.h"

#include "ASTNodeString.h"

EventRecorder::EventRecorder(Parser& parser) : InterpreterBase(parser) {
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

void EventRecorder::visitBeginBlockDecl(BeginBlockDeclEvent& event) {
    _events.emplace_back("BeginBlockDecl");
}

void EventRecorder::visitEndBlockDecl(EndBlockDeclEvent& event) {
    _events.emplace_back("EndBlockDecl");
}

void EventRecorder::visitBeginIfDecl(BeginIfDeclEvent& event) {
    _events.emplace_back("BeginIfDecl");
}

void EventRecorder::visitEndIfDecl(EndIfDeclEvent& event) {
    _events.emplace_back("EndIfDecl");
}
