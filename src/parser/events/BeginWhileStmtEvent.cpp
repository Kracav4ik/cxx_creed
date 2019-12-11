#include "BeginWhileStmtEvent.h"
#include "parser/EventVisitor.h"

BeginWhileStmtEvent::BeginWhileStmtEvent(ASTNodePtr value) : expr(std::move(value)) {}

void BeginWhileStmtEvent::visit(EventVisitor& visitor) {
    visitor.visitBeginWhileStmt(*this);
}
