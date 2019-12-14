#pragma once

#include "SpecialType.h"

class CoutValue;
class CoutType : public SpecialType<CoutValue, CoutType> {
friend class SingletonType<CoutType>;
public:
    std::string type_name() const override;

private:
    CoutType() = default;
};
