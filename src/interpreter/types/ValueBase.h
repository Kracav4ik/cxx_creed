#pragma once

#include "ValueFwd.h"

class TypeBase;
class ValueBase {
public:
    virtual ~ValueBase() = default;

    virtual ValuePtr binary_op(const std::string& op, const ValuePtr& right) const = 0;
    virtual ValuePtr unary_op(const std::string& op) const = 0;
    virtual bool is_true() const = 0;

    virtual ValuePtr copy() const = 0;
    virtual std::string printable_str() const = 0;
    virtual TypePtr get_type() const = 0;
};
