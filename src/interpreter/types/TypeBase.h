#pragma once

#include "ValueFwd.h"

#include <string>

class TypeBase {
public:
    TypeBase() = default;
    TypeBase(const TypeBase&) = delete;
    TypeBase& operator=(const TypeBase&) = delete;

    virtual ValuePtr create_value() const = 0;
    virtual ValuePtr binary_op(const ValueBase& left, const std::string& op, const ValueBase& right) const = 0;
    virtual ValuePtr unary_op(const std::string& op, const ValueBase& value) const = 0;
    virtual bool is_true(const ValueBase& value) const = 0;
};
