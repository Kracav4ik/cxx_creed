#include "ParseErrorEvent.h"
#include "parser/EventVisitor.h"

void ParseErrorEvent::visit(EventVisitor& visitor) {
    visitor.visitParseError(*this);
}

ParseErrorEvent::ParseErrorEvent(Token token) : token(std::move(token)) {}
