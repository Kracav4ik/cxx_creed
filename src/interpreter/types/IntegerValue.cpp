#include "IntegerValue.h"
#include "IntegerType.h"

#include <cassert>

namespace {
    int bool_convert(bool val) {
        return val ? IntegerType::TRUE_VALUE : IntegerType::FALSE_VALUE;
    }
}

IntegerValue::IntegerValue(int value) : _value(value) {
}

int IntegerValue::get_value() const {
    return _value;
}

ValuePtr IntegerValue::copy() const {
    return std::make_shared<IntegerValue>(*this);
}

bool IntegerValue::is_true() const {
    return _value != IntegerType::FALSE_VALUE;
}

std::string IntegerValue::printable_str() const {
    return std::to_string(_value);
}

ValuePtr IntegerValue::binary_add(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value + other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_sub(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value - other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_mul(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value * other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_div(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value / other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_mod(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value % other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_xor(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value ^ other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_bitand(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value & other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_bitor(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value | other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_lshift(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value << other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_rshift(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(_value >> other_int->_value);
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_eq(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(bool_convert(_value == other_int->_value));
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_noteq(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(bool_convert(_value != other_int->_value));
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_lt(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(bool_convert(_value < other_int->_value));
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_lteq(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(bool_convert(_value <= other_int->_value));
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_gt(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(bool_convert(_value > other_int->_value));
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::binary_gteq(const ValuePtr& other) const {
    if (auto other_int = std::dynamic_pointer_cast<IntegerValue>(other)) {
        IntegerType type;  // TODO: don't hardcode type
        return type.create_value(bool_convert(_value >= other_int->_value));
    }
    assert(false);
    return nullptr;
}

ValuePtr IntegerValue::unary_plus() const {
    IntegerType type;  // TODO: don't hardcode type
    return type.create_value(_value);
}

ValuePtr IntegerValue::unary_minus() const {
    IntegerType type;  // TODO: don't hardcode type
    return type.create_value(-_value);
}

ValuePtr IntegerValue::unary_compl() const {
    IntegerType type;  // TODO: don't hardcode type
    return type.create_value(~_value);
}

ValuePtr IntegerValue::unary_not() const {
    IntegerType type;  // TODO: don't hardcode type
    return type.create_value(bool_convert(!is_true()));
}
