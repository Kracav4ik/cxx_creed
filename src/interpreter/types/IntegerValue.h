#pragma once

#include "ValueBase.h"

class IntegerValue : public ValueBase {
public:
    IntegerValue(int value = 0);
    int get_value() const;

    ValuePtr copy() const override;
    bool is_true() const override;
    std::string printable_str() const override;

    ValuePtr binary_add(const ValuePtr& other) const override;
    ValuePtr binary_sub(const ValuePtr& other) const override;
    ValuePtr binary_mul(const ValuePtr& other) const override;
    ValuePtr binary_div(const ValuePtr& other) const override;
    ValuePtr binary_mod(const ValuePtr& other) const override;
    ValuePtr binary_xor(const ValuePtr& other) const override;
    ValuePtr binary_bitand(const ValuePtr& other) const override;
    ValuePtr binary_bitor(const ValuePtr& other) const override;
    ValuePtr binary_lshift(const ValuePtr& other) const override;
    ValuePtr binary_rshift(const ValuePtr& other) const override;
    ValuePtr binary_eq(const ValuePtr& other) const override;
    ValuePtr binary_noteq(const ValuePtr& other) const override;
    ValuePtr binary_lt(const ValuePtr& other) const override;
    ValuePtr binary_lteq(const ValuePtr& other) const override;
    ValuePtr binary_gt(const ValuePtr& other) const override;
    ValuePtr binary_gteq(const ValuePtr& other) const override;

    ValuePtr unary_plus() const override;
    ValuePtr unary_minus() const override;
    ValuePtr unary_compl() const override;
    ValuePtr unary_not() const override;

private:
    int _value;
};
