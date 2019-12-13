#include "IncludeEvent.h"
#include "parser/EventVisitor.h"

IncludeEvent::IncludeEvent(std::string include) : include(std::move(include)) {}

void IncludeEvent::visit(EventVisitor& visitor) {
    visitor.visitInclude(*this);
}
