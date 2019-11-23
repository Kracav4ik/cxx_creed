#include "EndMainDeclEvent.h"
#include "parser/EventVisitor.h"

void EndMainDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitEndMainDecl(*this);
}
