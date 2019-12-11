#include "EndWhileDeclEvent.h"
#include "parser/EventVisitor.h"

void EndWhileDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitEndWhileDecl(*this);
}
