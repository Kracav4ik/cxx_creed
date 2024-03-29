#pragma once

#include "SpecialValue.h"
#include <memory>

class CoutType;
template <typename TypeValue, typename TypeClass> class SpecialType;

class CoutValue : public SpecialValue<CoutType>, public std::enable_shared_from_this<CoutValue> {
friend class SpecialType<CoutValue, CoutType>;
public:
    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const override;
    std::string printable_str() const override;

private:
    CoutValue() = default;
};
