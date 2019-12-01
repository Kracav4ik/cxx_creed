#include "AssignmentNode.h"
#include "expression_parser/ASTVisitor.h"

AssignmentNode::AssignmentNode(ASTNodePtr left, ASTNodePtr right)
        : left(std::move(left))
        , right(std::move(right))
{
}

void AssignmentNode::visit(ASTVisitor& visitor) {
    visitor.visitAssignment(*this);
}
