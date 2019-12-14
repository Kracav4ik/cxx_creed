#pragma once

#include "RealValueBase.h"

class IntegerType;
class IntegerValue : public RealValueBase<IntegerValue, IntegerType> {
public:
    IntegerValue(int value = 0);
    int get_value() const;

    std::string printable_str() const override;

private:
    int _value;
};
