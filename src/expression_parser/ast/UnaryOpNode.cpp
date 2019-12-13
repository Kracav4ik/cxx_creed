#include "UnaryOpNode.h"

#include "expression_parser/ASTVisitor.h"

void UnaryOpNode::visit(ASTVisitor& visitor) const {
    visitor.visitUnaryOp(*this);
}

UnaryOpNode::UnaryOpNode(std::string op, std::string text, ASTNodePtr subnode)
        : op(std::move(op))
        , text(std::move(text))
        , subnode(std::move(subnode))
{
}
