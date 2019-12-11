#include "BeginBlockStmtEvent.h"
#include "parser/EventVisitor.h"

void BeginBlockStmtEvent::visit(EventVisitor& visitor) {
    visitor.visitBeginBlockStmt(*this);
}
