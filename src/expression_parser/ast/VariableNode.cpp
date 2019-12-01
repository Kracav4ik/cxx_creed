#include "VariableNode.h"
#include "expression_parser/ASTVisitor.h"

VariableNode::VariableNode(std::string value) : var_name(std::move(value)) {}

void VariableNode::visit(ASTVisitor& visitor) {
    visitor.visitVariable(*this);
}
