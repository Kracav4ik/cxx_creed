#include "EndIfStmtEvent.h"
#include "parser/EventVisitor.h"

void EndIfStmtEvent::visit(EventVisitor& visitor) {
    visitor.visitEndIfStmt(*this);
}
