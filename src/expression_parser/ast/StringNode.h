#pragma once

#include "ASTNode.h"

#include <string>

struct StringNode : ASTNode {
    explicit StringNode(std::string raw_value);
    void visit(ASTVisitor& visitor) const override;

    std::string value() const;
    std::string raw_value;
};
