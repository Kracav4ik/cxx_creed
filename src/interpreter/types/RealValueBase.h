#pragma once

#include "ValueWithType.h"

template <typename ValueClass, typename TypeClass>
class RealValueBase : public ValueWithType<TypeClass> {
public:
    using FieldType = typename TypeClass::FieldType;
    using ValueWithType<TypeClass>::get_real_type;

    explicit RealValueBase(FieldType value);

    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const final;
    ValuePtr unary_op(const std::string& op) const final;
    bool is_true() const final;

    FieldType get_value() const;
    void set_value(FieldType value);

private:
    FieldType _value;
};
