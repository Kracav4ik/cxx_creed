#include "ExprStmtEvent.h"
#include "parser/EventVisitor.h"

ExprStmtEvent::ExprStmtEvent(ASTNodePtr value) : expr(std::move(value)) {}

void ExprStmtEvent::visit(EventVisitor& visitor) {
    visitor.visitExprStmt(*this);
}
