#pragma once

#include "ValueBase.h"
#include "CoutType.h"
#include <memory>

class CoutValue : public ValueBase, public std::enable_shared_from_this<CoutValue> {
friend CoutType;
public:
    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const override;
    ValuePtr unary_op(const std::string& op) const override;
    bool is_true() const override;

    std::string printable_str() const override;
    TypePtr get_type() const override;

    CoutValue(const CoutValue&) = delete;
    CoutValue& operator=(const CoutValue&) = delete;

private:
    CoutValue() = default;
};
