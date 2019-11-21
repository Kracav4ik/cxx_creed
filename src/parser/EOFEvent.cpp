#include "EOFEvent.h"
#include "parser/EventVisitor.h"

void EOFEvent::visit(EventVisitor& visitor) {
    visitor.visitEOF(*this);
}
