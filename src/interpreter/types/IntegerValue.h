#pragma once

#include "RealValueBase.h"

class IntegerType;
class IntegerValue : public RealValueBase<IntegerValue, IntegerType> {
public:
    IntegerValue(int value = 0);
    int get_value() const;

    ValuePtr copy() const override;
    std::string printable_str() const override;

    std::shared_ptr<IntegerType> get_real_type() const override;

private:
    int _value;
};
