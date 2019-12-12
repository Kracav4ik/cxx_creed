#pragma once

#include "ValueFwd.h"

class TypeBase;
class ValueBase {
public:
    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const;
    ValuePtr unary_op(const std::string& op) const;
    bool is_true() const;

    virtual ValuePtr copy() const = 0;
    virtual std::string printable_str() const = 0;
    virtual std::shared_ptr<TypeBase> get_type() const = 0;
};
