#include "ASTNodeString.h"

#include "expression_parser/ast/BinaryOpNode.h"
#include "expression_parser/ast/UnaryOpNode.h"
#include "expression_parser/ast/IntegerNode.h"
#include "expression_parser/ast/StringNode.h"
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

void ASTNodeString::visitBinaryOp(const BinaryOpNode& node) {
    _buf << "[BinaryOp ";
    node.left->visit(*this);
    _buf << " " << node.text << " ";
    node.right->visit(*this);
    _buf << "]";
}

void ASTNodeString::visitUnaryOp(const UnaryOpNode& node) {
    _buf << "[UnaryOp ";
    _buf << node.text << " ";
    node.subnode->visit(*this);
    _buf << "]";
}

void ASTNodeString::visitInteger(const IntegerNode& node) {
    _buf << "[Integer " << node.value << "]";
}

void ASTNodeString::visitString(const StringNode& node) {
    _buf << "[String " << node.raw_value << "]";
}

void ASTNodeString::visitAssignment(const AssignmentNode& node) {
    _buf << "[AssignmentOp ";
    node.left->visit(*this);
    _buf << " = ";
    node.right->visit(*this);
    _buf << "]";
}

void ASTNodeString::visitVariable(const VariableNode& node) {
    _buf << "[Variable " << node.var_name << "]";
}
