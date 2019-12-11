#include "EndWhileStmtEvent.h"
#include "parser/EventVisitor.h"

void EndWhileStmtEvent::visit(EventVisitor& visitor) {
    visitor.visitEndWhileStmt(*this);
}
