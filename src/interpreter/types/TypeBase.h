#pragma once

#include "ValueFwd.h"

#include <string>

class TypeBase {
public:
    TypeBase() = default;
    TypeBase(const TypeBase&) = delete;
    TypeBase& operator=(const TypeBase&) = delete;
    virtual ~TypeBase() = default;

    virtual ValuePtr create_empty_value() const = 0;
    virtual std::string type_name() const = 0;
};
