#pragma once

#include "TypeBase.h"
#include <unordered_map>
#include <string>
#include <functional>

class IntegerValue;
class IntegerType : public TypeBase {
public:
    ValuePtr create_value() const override;
    ValuePtr binary_op(const ValueBase& left, const std::string& op, const ValueBase& right) const override;
    ValuePtr unary_op(const std::string& op, const ValueBase& value) const override;
    bool is_true(const ValueBase& value) const override;

    ValuePtr create_value(int value) const;
    ValuePtr create_false() const;
    ValuePtr create_true() const;

    static std::shared_ptr<IntegerType> get();

private:
    static const int FALSE_VALUE = 0;
    static const int TRUE_VALUE = 1;

    IntegerType();

    static int bool_convert(bool val);
    static bool is_true_value(int val);

    std::unordered_map<std::string, std::function<int(int, int)>> _binary_ops;
    std::unordered_map<std::string, std::function<int(int)>> _unary_ops;
};
