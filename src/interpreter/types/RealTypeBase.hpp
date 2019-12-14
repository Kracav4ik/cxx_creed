#pragma once

#include "RealTypeBase.h"
#include "ValueBase.h"

#include "interpreter/exceptions/UnknownOpException.h"
#include "interpreter/exceptions/OperandTypeException.h"

template <typename ValueClass, typename TypeClass, typename UnderlyingType>
ValuePtr RealTypeBase<ValueClass, TypeClass, UnderlyingType>::create_empty_value() const {
    return create_value(UnderlyingType());
}

template <typename ValueClass, typename TypeClass, typename UnderlyingType>
ValuePtr RealTypeBase<ValueClass, TypeClass, UnderlyingType>::binary_op(const ValueClass& left, const std::string& op, const ValueBase& right) const {
    auto op_it = _binary_ops.find(op);
    if (op_it == _binary_ops.end()) {
        throw UnknownOpException("Unknown binary op token " + op);
    }
    if (auto right_casted = dynamic_cast<const ValueClass*>(&right)) {
        UnderlyingType result = op_it->second(left.get_value(), right_casted->get_value());
        return create_value(std::move(result));
    }
    throw OperandTypeException("Bad types '" + left.get_type()->type_name() + "' and '" + right.get_type()->type_name() + "' for binary op token " + op);
}

template <typename ValueClass, typename TypeClass, typename UnderlyingType>
ValuePtr RealTypeBase<ValueClass, TypeClass, UnderlyingType>::unary_op(const std::string& op, const ValueClass& value) const {
    auto op_it = _unary_ops.find(op);
    if (op_it == _unary_ops.end()) {
        throw UnknownOpException("Unknown unary op token " + op);
    }
    UnderlyingType result = op_it->second(value.get_value());
    return create_value(std::move(result));
}

template <typename ValueClass, typename TypeClass, typename UnderlyingType>
void RealTypeBase<ValueClass, TypeClass, UnderlyingType>::installBinaryOp(std::string op, BinaryOpFunc func) {
    _binary_ops.emplace(std::move(op), std::move(func));
}

template <typename ValueClass, typename TypeClass, typename UnderlyingType>
void RealTypeBase<ValueClass, TypeClass, UnderlyingType>::installUnaryOp(std::string op, UnaryOpFunc func) {
    _unary_ops.emplace(std::move(op), std::move(func));
}
