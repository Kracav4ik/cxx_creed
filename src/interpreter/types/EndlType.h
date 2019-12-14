#pragma once
#include "TypeBase.h"

class EndlType : public TypeBase {
public:
    ValuePtr create_empty_value() const override;
    std::string type_name() const override;
    bool can_assign(ValuePtr ptr) const override;

    static std::shared_ptr<EndlType> get();

    EndlType(const EndlType&) = delete;
    EndlType& operator=(const EndlType&) = delete;

private:
    EndlType() = default;
};
