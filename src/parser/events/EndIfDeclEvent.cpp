#include "EndIfDeclEvent.h"
#include "parser/EventVisitor.h"

void EndIfDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitEndIfDecl(*this);
}
