#include "BeginIfStmtEvent.h"
#include "parser/EventVisitor.h"

void BeginIfStmtEvent::visit(EventVisitor& visitor) {
    visitor.visitBeginIfStmt(*this);
}

BeginIfStmtEvent::BeginIfStmtEvent(ASTNodePtr value) : expr(std::move(value)) {}
