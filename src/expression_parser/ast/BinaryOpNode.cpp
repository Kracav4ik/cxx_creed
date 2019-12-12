#include "BinaryOpNode.h"

#include "expression_parser/ASTVisitor.h"

void BinaryOpNode::visit(ASTVisitor& visitor) {
    visitor.visitBinaryOp(*this);
}

BinaryOpNode::BinaryOpNode(std::string op, std::string text, ASTNodePtr left, ASTNodePtr right)
    : op(std::move(op))
    , text(std::move(text))
    , left(std::move(left))
    , right(std::move(right))
{
}
