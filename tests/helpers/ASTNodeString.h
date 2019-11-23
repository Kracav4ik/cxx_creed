#pragma once

#include "parser/ASTVisitor.h"
#include "parser/ast/ASTNode.h"

#include <sstream>
#include <string>

class ASTNodeString : ASTVisitor {
public:
    ASTNodeString(const ASTNodePtr& node);
    std::string str() const;

private:
    void visitBinaryOp(BinaryOpNode& node) override;
    void visitInteger(IntegerNode& node) override;

    std::stringstream _buf;
};
