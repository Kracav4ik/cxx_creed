#pragma once

#include "RealValueBase.h"

#include <cassert>

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
std::shared_ptr<TypeBase> RealValueBase<ValueClass, TypeClass>::get_type() const {
    return get_real_type();
}
