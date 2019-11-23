#include "ASTNodeString.h"

#include "parser/ast/BinaryOpNode.h"
#include "parser/ast/IntegerNode.h"

ASTNodeString::ASTNodeString(const ASTNodePtr& node) {
    node->visit(*this);
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

void ASTNodeString::visitInteger(IntegerNode& node) {
    _buf << "[Integer " << node.value << "]";
}
