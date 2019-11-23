#include "UnknownTokenEvent.h"
#include "parser/EventVisitor.h"

UnknownTokenEvent::UnknownTokenEvent(std::string token_text)  : token_text(std::move(token_text)) {}

void UnknownTokenEvent::visit(EventVisitor& visitor) {
    visitor.visitUnknownToken(*this);
}
