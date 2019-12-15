#pragma once

#include "SingletonType.h"

#include <unordered_map>
#include <functional>
#include <string>
#include <type_traits>

template <typename ValueClass, typename TypeClass, typename UnderlyingType>
class RealTypeBase : public SingletonType<TypeClass> {
public:
    using FieldType = UnderlyingType;
    using ArgType = std::conditional_t<std::is_arithmetic_v<UnderlyingType>, UnderlyingType, const UnderlyingType&>;
    using BinaryOpFunc = std::function<UnderlyingType(ArgType, ArgType)>;
    using UnaryOpFunc = std::function<UnderlyingType(ArgType)>;
    using GeneralBinaryOpFunc = std::function<ValuePtr(ArgType, ArgType)>;
    using GeneralUnaryOpFunc = std::function<ValuePtr(ArgType)>;

    using TypeBase::bool_convert;

    ValuePtr create_empty_value() const final;

    ValuePtr binary_op(const ValueClass& left, const std::string& op, const ValueBase& right) const;
    ValuePtr unary_op(const std::string& op, const ValueClass& value) const;
    virtual bool is_true(const ValueClass& value) const = 0;
    virtual ValuePtr create_value(ArgType value) const = 0;

    void installBinaryOp(std::string op, BinaryOpFunc func);
    void installGeneralBinaryOp(std::string op, GeneralBinaryOpFunc func);
    void installUnaryOp(std::string op, UnaryOpFunc func);
    void installGeneralUnaryOp(std::string op, GeneralUnaryOpFunc func);

protected:
    void installComparisonOps();

private:
    std::unordered_map<std::string, GeneralBinaryOpFunc> _binary_ops;
    std::unordered_map<std::string, GeneralUnaryOpFunc> _unary_ops;
};
