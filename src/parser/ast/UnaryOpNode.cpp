#include "UnaryOpNode.h"

#include "parser/ASTVisitor.h"

void UnaryOpNode::visit(ASTVisitor& visitor) {
    visitor.visitUnaryOp(*this);
}

UnaryOpNode::UnaryOpNode(std::string op, ASTNodePtr subnode)
        : op(std::move(op))
        , subnode(std::move(subnode))
{
}
