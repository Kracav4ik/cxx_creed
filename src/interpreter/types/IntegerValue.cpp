#include "IntegerValue.h"
#include "IntegerType.h"

IntegerValue::IntegerValue(int value) : _value(value) {
}

int IntegerValue::get_value() const {
    return _value;
}

ValuePtr IntegerValue::copy() const {
    return std::make_shared<IntegerValue>(*this);
}

std::string IntegerValue::printable_str() const {
    return std::to_string(_value);
}

std::shared_ptr<TypeBase> IntegerValue::get_type() const {
    return IntegerType::get();
}
