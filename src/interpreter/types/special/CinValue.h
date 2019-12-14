#pragma once

#include "SpecialValue.h"
#include <memory>

class CinType;
template <typename TypeValue, typename TypeClass> class SpecialType;

class CinValue : public SpecialValue<CinType>, public std::enable_shared_from_this<CinValue> {
friend class SpecialType<CinValue, CinType>;
public:
    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const override;
    std::string printable_str() const override;

private:
    CinValue() = default;
};
