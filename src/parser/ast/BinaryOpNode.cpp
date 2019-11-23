#include "BinaryOpNode.h"

#include "parser/ASTVisitor.h"

void BinaryOpNode::visit(ASTVisitor& visitor) {
    visitor.visitBinaryOp(*this);
}

BinaryOpNode::BinaryOpNode(std::string op, ASTNodePtr left, ASTNodePtr right)
    : op(std::move(op))
    , left(std::move(left))
    , right(std::move(right))
{
}
