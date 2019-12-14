#pragma once

#include "TypeBase.h"

class CoutType : public TypeBase {
public:
    ValuePtr create_empty_value() const override;
    std::string type_name() const override;
    bool can_assign(ValuePtr ptr) const override;

    static std::shared_ptr<CoutType> get();

    CoutType(const CoutType&) = delete;
    CoutType& operator=(const CoutType&) = delete;

private:
    CoutType() = default;
};
