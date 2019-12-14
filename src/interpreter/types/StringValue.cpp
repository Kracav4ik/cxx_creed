#include "StringValue.h"

#include "RealValueBase.hpp"
#include "RealTypeBase.hpp"
#include "StringType.h"

#include <utility>

StringValue::StringValue(std::string  value) : _value(std::move(value)) {
}

std::string StringValue::get_value() const {
    return _value;
}

std::string StringValue::printable_str() const {
    return get_value();
}
