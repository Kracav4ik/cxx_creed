#pragma once
#include "SpecialType.h"

class EndlValue;
class EndlType : public SpecialType<EndlValue, EndlType> {
friend class SingletonType<EndlType>;
public:
    std::string type_name() const override;

private:
    EndlType() = default;
};
