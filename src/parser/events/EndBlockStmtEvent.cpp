#include "EndBlockStmtEvent.h"
#include "parser/EventVisitor.h"

void EndBlockStmtEvent::visit(EventVisitor& visitor) {
    visitor.visitEndBlockStmt(*this);
}
