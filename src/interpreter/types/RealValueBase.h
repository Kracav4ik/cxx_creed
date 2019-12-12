#pragma once

#include "ValueBase.h"

template <typename ValueClass, typename TypeClass>
class RealValueBase : public ValueBase {
public:
    ValuePtr binary_op(const std::string& op, const ValuePtr& right) const final;
    ValuePtr unary_op(const std::string& op) const final;
    bool is_true() const final;

    TypePtr get_type() const final;

    virtual std::shared_ptr<TypeClass> get_real_type() const = 0;
};
