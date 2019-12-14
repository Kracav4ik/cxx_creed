#pragma once
#pragma once

#include "interpreter/types/ValueBase.h"
#include <memory>

class EndlType;
template <typename TypeValue, typename TypeClass> class SpecialType;

class EndlValue : public ValueBase, public std::enable_shared_from_this<EndlValue> {
friend class SpecialType<EndlValue, EndlType>;
public:
    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const override;
    ValuePtr unary_op(const std::string& op) const override;
    bool is_true() const override;

    std::string printable_str() const override;
    TypePtr get_type() const override;

    EndlValue(const EndlValue&) = delete;
    EndlValue& operator=(const EndlValue&) = delete;

private:
    EndlValue() = default;
};
