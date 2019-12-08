#include "BeginBlockDeclEvent.h"
#include "parser/EventVisitor.h"

void BeginBlockDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitBeginBlockDecl(*this);
}
