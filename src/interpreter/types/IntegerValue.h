#pragma once

#include "ValueBase.h"

class IntegerValue : public ValueBase {
public:
    IntegerValue(int value = 0);
    int get_value() const;

    ValuePtr copy() const override;
    std::string printable_str() const override;
    std::shared_ptr<TypeBase> get_type() const override;

private:
    int _value;
};
