#include "ReturnStmtEvent.h"
#include "parser/EventVisitor.h"

void ReturnStmtEvent::visit(EventVisitor& visitor) {
    visitor.visitReturnStmt(*this);
}
