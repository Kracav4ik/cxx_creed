#include "UnknownTokenTypeEvent.h"
#include "parser/EventVisitor.h"

UnknownTokenTypeEvent::UnknownTokenTypeEvent(std::string token_type)  : token_type(std::move(token_type)) {}

void UnknownTokenTypeEvent::visit(EventVisitor& visitor) {
    visitor.visitUnknownTokenType(*this);
}
