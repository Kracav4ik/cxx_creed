#include "BeginMainDeclEvent.h"
#include "parser/EventVisitor.h"

void BeginMainDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitBeginMainDecl(*this);
}
