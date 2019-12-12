#pragma once

#include "TypeBase.h"

#include <unordered_map>
#include <functional>
#include <type_traits>

template <typename ValueClass, typename UnderlyingType>
class RealTypeBase : public TypeBase {
public:
    using ArgType = std::conditional_t<std::is_arithmetic_v<UnderlyingType>, UnderlyingType, const UnderlyingType&>;
    using BinaryOpFunc = std::function<UnderlyingType(ArgType, ArgType)>;
    using UnaryOpFunc = std::function<UnderlyingType(ArgType)>;

    ValuePtr create_empty_value() const final;

    ValuePtr binary_op(const ValueClass& left, const std::string& op, const ValueBase& right) const;
    ValuePtr unary_op(const std::string& op, const ValueClass& value) const;
    virtual bool is_true(const ValueClass& value) const = 0;
    virtual ValuePtr create_value(UnderlyingType value) const = 0;

    void installBinaryOp(std::string op, BinaryOpFunc func);
    void installUnaryOp(std::string op, UnaryOpFunc func);

private:
    std::unordered_map<std::string, BinaryOpFunc> _binary_ops;
    std::unordered_map<std::string, UnaryOpFunc> _unary_ops;
};
