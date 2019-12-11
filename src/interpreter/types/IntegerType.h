#pragma once

#include "TypeBase.h"

class IntegerValue;
class IntegerType : public TypeBase {
public:
    ValuePtr create_value() const override;
    ValuePtr create_value(int value) const;

    ValuePtr create_false() const;
    ValuePtr create_true() const;

    static const int FALSE_VALUE = 0;
    static const int TRUE_VALUE = 1;
};
