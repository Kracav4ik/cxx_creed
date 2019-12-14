#pragma once

#include "SpecialValue.h"
#include "interpreter/exceptions/UnknownOpException.h"

template <typename TypeClass>
ValuePtr SpecialValue<TypeClass>::binary_op(const std::string& op, const ValuePtr& right) const {
    throw UnknownOpException("Unknown binary op token " + op);
}

template <typename TypeClass>
ValuePtr SpecialValue<TypeClass>::unary_op(const std::string& op) const {
    throw UnknownOpException("Unknown unary op token " + op);
}

template <typename TypeClass>
bool SpecialValue<TypeClass>::is_true() const {
    return true;
}
