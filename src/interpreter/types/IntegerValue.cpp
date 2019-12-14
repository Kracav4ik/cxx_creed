#include "IntegerValue.h"
#include "RealValueBase.hpp"
#include "RealTypeBase.hpp"
#include "IntegerType.h"

IntegerValue::IntegerValue(int value) : _value(value) {
}

int IntegerValue::get_value() const {
    return _value;
}

std::string IntegerValue::printable_str() const {
    return std::to_string(_value);
}

std::shared_ptr<IntegerType> IntegerValue::get_real_type() const {
    return IntegerType::get();
}
