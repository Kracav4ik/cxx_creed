#include "BeginWhileDeclEvent.h"
#include "parser/EventVisitor.h"

BeginWhileDeclEvent::BeginWhileDeclEvent(ASTNodePtr value) : expr(std::move(value)) {}

void BeginWhileDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitBeginWhileDecl(*this);
}
