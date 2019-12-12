#include "VarDeclEvent.h"
#include "parser/EventVisitor.h"

VarDeclEvent::VarDeclEvent(std::string type_name, std::string var_name) : type_name(std::move(type_name)), var_name(std::move(var_name)) {}

void VarDeclEvent::visit(EventVisitor& visitor) {
    visitor.visitVarDecl(*this);
}
