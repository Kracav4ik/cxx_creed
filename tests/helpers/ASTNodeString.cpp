#include "ASTNodeString.h"

#include "expression_parser/ast/BinaryOpNode.h"
#include "expression_parser/ast/UnaryOpNode.h"
#include "expression_parser/ast/IntegerNode.h"
#include "expression_parser/ast/AssignmentNode.h"
#include "expression_parser/ast/VariableNode.h"

ASTNodeString::ASTNodeString(const ASTNodePtr& node) {
    if (node) {
        node->visit(*this);
    }
}

std::string ASTNodeString::str() const {
    return _buf.str();
}

void ASTNodeString::visitBinaryOp(BinaryOpNode& node) {
    _buf << "[BinaryOp ";
    node.left->visit(*this);
    _buf << " " << node.op << " ";
    node.right->visit(*this);
    _buf << "]";
}

void ASTNodeString::visitUnaryOp(UnaryOpNode& node) {
    _buf << "[UnaryOp ";
    _buf << node.op << " ";
    node.subnode->visit(*this);
    _buf << "]";
}

void ASTNodeString::visitInteger(IntegerNode& node) {
    _buf << "[Integer " << node.value << "]";
}

void ASTNodeString::visitAssignment(AssignmentNode& node) {
    _buf << "[AssignmentOp ";
    node.left->visit(*this);
    _buf << " = ";
    node.right->visit(*this);
    _buf << "]";
}

void ASTNodeString::visitVariable(VariableNode& node) {
    _buf << "[Variable " << node.var_name << "]";
}
