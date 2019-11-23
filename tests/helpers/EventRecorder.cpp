#include "EventRecorder.h"

#include "parser/ParseErrorEvent.h"
#include "parser/ReturnStmtEvent.h"
#include "parser/UnknownTokenTypeEvent.h"
#include "parser/UnknownTokenEvent.h"

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
    _events.emplace_back("ReturnStmt " + event.value);
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
