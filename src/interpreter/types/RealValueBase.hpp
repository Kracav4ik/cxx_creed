#pragma once

#include "RealValueBase.h"

#include <cassert>

template <typename ValueClass, typename TypeClass>
RealValueBase<ValueClass, TypeClass>::RealValueBase(FieldType value) : _value(std::move(value)) {}

template <typename ValueClass, typename TypeClass>
ValuePtr RealValueBase<ValueClass, TypeClass>::binary_op(const std::string& op, const ValuePtr& right) const {
    assert(right);  // TODO: throw
    return get_real_type()->binary_op(*static_cast<const ValueClass*>(this), op, *right);
}

template <typename ValueClass, typename TypeClass>
ValuePtr RealValueBase<ValueClass, TypeClass>::unary_op(const std::string& op) const {
    return get_real_type()->unary_op(op, *static_cast<const ValueClass*>(this));
}

template <typename ValueClass, typename TypeClass>
bool RealValueBase<ValueClass, TypeClass>::is_true() const {
    return get_real_type()->is_true(*static_cast<const ValueClass*>(this));
}

template <typename ValueClass, typename TypeClass>
auto RealValueBase<ValueClass, TypeClass>::get_value() const -> FieldType {
    return _value;
}

template <typename ValueClass, typename TypeClass>
void RealValueBase<ValueClass, TypeClass>::set_value(FieldType value) {
    _value = std::move(value);
}
