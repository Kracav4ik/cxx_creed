#include "BeginIfDeclEvent.h"
#include "parser/EventVisitor.h"

void BeginIfDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitBeginIfDecl(*this);
}

BeginIfDeclEvent::BeginIfDeclEvent(ASTNodePtr value) : expr(std::move(value)) {}
