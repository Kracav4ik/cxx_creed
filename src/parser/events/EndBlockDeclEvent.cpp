#include "EndBlockDeclEvent.h"
#include "parser/EventVisitor.h"

void EndBlockDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitEndBlockDecl(*this);
}
