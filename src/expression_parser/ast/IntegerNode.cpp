#include "IntegerNode.h"

#include "expression_parser/ASTVisitor.h"

IntegerNode::IntegerNode(int value) : value(value) {}

void IntegerNode::visit(ASTVisitor& visitor) const {
    visitor.visitInteger(*this);
}
