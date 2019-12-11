#pragma once

#include "ValueFwd.h"

class ValueBase {
public:
    // TODO: virtual std::shared_ptr<TypeBase> get_type() const = 0;
    virtual ValuePtr copy() const = 0;
    virtual bool is_true() const = 0;
    virtual std::string printable_str() const = 0;

    virtual ValuePtr binary_add(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_sub(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_mul(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_div(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_mod(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_xor(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_bitand(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_bitor(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_lshift(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_rshift(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_eq(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_noteq(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_lt(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_lteq(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_gt(const ValuePtr& other) const = 0;
    virtual ValuePtr binary_gteq(const ValuePtr& other) const = 0;

    virtual ValuePtr unary_plus() const = 0;
    virtual ValuePtr unary_minus() const = 0;
    virtual ValuePtr unary_compl() const = 0;
    virtual ValuePtr unary_not() const = 0;
};
