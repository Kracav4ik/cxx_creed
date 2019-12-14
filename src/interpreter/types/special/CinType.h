#pragma once

#include "SpecialType.h"

class CinValue;
class CinType : public SpecialType<CinValue, CinType> {
    friend class SingletonType<CinType>;
public:
    std::string type_name() const override;

private:
    CinType() = default;
};
