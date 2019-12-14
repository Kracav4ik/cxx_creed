#pragma once
#pragma once

#include "ValueBase.h"
#include "EndlType.h"
#include <memory>

class EndlValue : public ValueBase, public std::enable_shared_from_this<EndlValue> {
friend EndlType;
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
