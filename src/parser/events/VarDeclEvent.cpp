#include "VarDeclEvent.h"
#include "parser/EventVisitor.h"

VarDeclEvent::VarDeclEvent(std::string value) : var_name(std::move(value)) {}

void VarDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitVarDecl(*this);
}
