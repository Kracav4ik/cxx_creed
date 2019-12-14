#pragma once

#include "interpreter/types/ValueBase.h"
#include <memory>

class CoutType;
template <typename TypeValue, typename TypeClass> class SpecialType;

class CoutValue : public ValueBase, public std::enable_shared_from_this<CoutValue> {
friend class SpecialType<CoutValue, CoutType>;
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
