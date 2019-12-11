#pragma once

#include "ValueBase.h"

class TypeBase {
public:
    virtual ValuePtr create_value() const = 0;
};
