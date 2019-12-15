#pragma once

#include "interpreter/types/ValueWithType.h"
#include <memory>

template <typename TypeClass>
class SpecialValue : public ValueWithType<TypeClass> {
public:
    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const override;
    ValuePtr unary_op(const std::string& op) const override;
    bool is_true() const override;
    void visit(ValueVisitor& visitor) final;

    SpecialValue(const SpecialValue&) = delete;
    SpecialValue& operator=(const SpecialValue&) = delete;
    SpecialValue() = default;
};
