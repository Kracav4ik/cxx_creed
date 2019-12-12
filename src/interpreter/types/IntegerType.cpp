#include "IntegerType.h"
#include "IntegerValue.h"

#include <cassert>

ValuePtr IntegerType::create_value() const {
    return std::make_shared<IntegerValue>();
}

ValuePtr IntegerType::create_value(int value) const {
    return std::make_shared<IntegerValue>(value);
}

ValuePtr IntegerType::create_false() const {
    return create_value(FALSE_VALUE);
}

ValuePtr IntegerType::create_true() const {
    return create_value(TRUE_VALUE);
}

std::shared_ptr<IntegerType> IntegerType::get() {
    static std::shared_ptr<IntegerType> res(new IntegerType());
    return res;
}

IntegerType::IntegerType() {
    _binary_ops["ADD"] = [](int a, int b) { return a + b; };  // TODO: check value
    _binary_ops["SUB"] = [](int a, int b) { return a - b; };  // TODO: check value
    _binary_ops["MUL"] = [](int a, int b) { return a * b; };  // TODO: check value
    _binary_ops["DIV"] = [](int a, int b) { return a / b; };  // TODO: check value and div by zero
    _binary_ops["MOD"] = [](int a, int b) { return a % b; };  // TODO: check value and div by zero
    _binary_ops["XOR"] = [](int a, int b) { return a ^ b; };
    _binary_ops["BITAND"] = [](int a, int b) { return a & b; };
    _binary_ops["BITOR"] = [](int a, int b) { return a | b; };
    _binary_ops["LSHIFT"] = [](int a, int b) { return a << b; };
    _binary_ops["RSHIFT"] = [](int a, int b) { return a >> b; };
    _binary_ops["EQ"] = [](int a, int b) { return bool_convert(a == b); };
    _binary_ops["NOTEQ"] = [](int a, int b) { return bool_convert(a != b); };
    _binary_ops["LT"] = [](int a, int b) { return bool_convert(a < b); };
    _binary_ops["LTEQ"] = [](int a, int b) { return bool_convert(a <= b); };
    _binary_ops["GT"] = [](int a, int b) { return bool_convert(a > b); };
    _binary_ops["GTEQ"] = [](int a, int b) { return bool_convert(a >= b); };

    _unary_ops["ADD"] = [](int a) { return a; };
    _unary_ops["SUB"] = [](int a) { return -a; };  // TODO: check value
    _unary_ops["NOT"] = [](int a) { return bool_convert(!is_true_value(a)); };
    _unary_ops["COMPL"] = [](int a) { return ~a; };
}

ValuePtr IntegerType::binary_op(const ValueBase& left, const std::string& op, const ValueBase& right) const {
    auto op_it = _binary_ops.find(op);
    if (op_it == _binary_ops.end()) {
        // TODO: throw
        assert(false);
    }
    if (auto left_int = dynamic_cast<const IntegerValue*>(&left)) {
        if (auto right_int = dynamic_cast<const IntegerValue*>(&right)) {
            int result = op_it->second(left_int->get_value(), right_int->get_value());
            return create_value(result);
        }
        // TODO: throw
        assert(false);
    }
    // TODO: throw
    assert(false);
}

ValuePtr IntegerType::unary_op(const std::string& op, const ValueBase& value) const {
    auto op_it = _unary_ops.find(op);
    if (op_it == _unary_ops.end()) {
        // TODO: throw
        assert(false);
    }
    if (auto value_int = dynamic_cast<const IntegerValue*>(&value)) {
        int result = op_it->second(value_int->get_value());
        return create_value(result);
    }
    // TODO: throw
    assert(false);
}

bool IntegerType::is_true(const ValueBase& value) const {
    if (auto value_int = dynamic_cast<const IntegerValue*>(&value)) {
        return is_true_value(value_int->get_value());
    }
    // TODO: throw
    assert(false);
}

int IntegerType::bool_convert(bool val) {
    return val ? IntegerType::TRUE_VALUE : IntegerType::FALSE_VALUE;
}

bool IntegerType::is_true_value(int val) {
    return val != IntegerType::FALSE_VALUE;
}
