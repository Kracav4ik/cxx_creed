#pragma once

#include "ValueWithType.h"

template <typename ValueClass, typename TypeClass>
class RealValueBase : public ValueWithType<TypeClass> {
public:
    using ValueWithType<TypeClass>::get_real_type;

    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const final;
    ValuePtr unary_op(const std::string& op) const final;
    bool is_true() const final;
};
