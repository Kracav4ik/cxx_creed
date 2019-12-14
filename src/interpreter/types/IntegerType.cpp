#include "IntegerType.h"
#include "IntegerValue.h"
#include "RealTypeBase.hpp"

#include "interpreter/exceptions/ArithmeticException.h"

bool IntegerType::is_true(const IntegerValue& value) const {
    return is_true_value(value.get_value());
}

ValuePtr IntegerType::create_value(int value) const {
    return std::make_shared<IntegerValue>(value);
}

std::string IntegerType::type_name() const {
    return "int";
}

ValuePtr IntegerType::create_false() {
    return get()->create_value(FALSE_VALUE);
}

ValuePtr IntegerType::create_true() {
    return get()->create_value(TRUE_VALUE);
}

IntegerType::IntegerType() {
    installBinaryOp("ADD", [](int a, int b) {
        int64_t to_check = (int64_t)a + (int64_t)b;
        check_value(to_check);
        return to_check;
    });
    installBinaryOp("SUB", [](int a, int b) {
        int64_t to_check = (int64_t)a - (int64_t)b;
        check_value(to_check);
        return to_check;
    });
    installBinaryOp("MUL", [](int a, int b) {
        int64_t to_check = (int64_t)a * (int64_t)b;
        check_value(to_check);
        return to_check;
    });
    installBinaryOp("DIV", [](int a, int b) {
        if (b == 0) {
            throw ArithmeticException("Integer division by zero", 0);
        }
        int64_t to_check = (int64_t)a / (int64_t)b;
        check_value(to_check);
        return to_check;
    });
    installBinaryOp("MOD", [](int a, int b) {
        if (b == 0) {
            throw ArithmeticException("Remainder of integer division by zero", 0);
        }
        int64_t to_check = (int64_t)a % (int64_t)b;
        check_value(to_check);
        return to_check;
    });

    installBinaryOp("XOR", [](int a, int b) { return a ^ b; });
    installBinaryOp("BITAND", [](int a, int b) { return a & b; });
    installBinaryOp("BITOR", [](int a, int b) { return a | b; });
    installBinaryOp("LSHIFT", [](int a, int b) { return a << b; });
    installBinaryOp("RSHIFT", [](int a, int b) { return a >> b; });
    installBinaryOp("EQ", [](int a, int b) { return bool_convert(a == b); });
    installBinaryOp("NOTEQ", [](int a, int b) { return bool_convert(a != b); });
    installBinaryOp("LT", [](int a, int b) { return bool_convert(a < b); });
    installBinaryOp("LTEQ", [](int a, int b) { return bool_convert(a <= b); });
    installBinaryOp("GT", [](int a, int b) { return bool_convert(a > b); });
    installBinaryOp("GTEQ", [](int a, int b) { return bool_convert(a >= b); });

    installUnaryOp("ADD", [](int a) { return a; });
    installUnaryOp("SUB", [](int a) {
        int64_t to_check = -(int64_t)a;
        check_value(to_check);
        return to_check;
    });
    installUnaryOp("NOT", [](int a) { return bool_convert(!is_true_value(a)); });
    installUnaryOp("COMPL", [](int a) { return ~a; });
}

void IntegerType::check_value(int64_t val) {
    if (val > std::numeric_limits<int>::max()) {
        throw ArithmeticException("Integer overflow: " + std::to_string(val) + " > " + std::to_string(std::numeric_limits<int>::max()), val);
    }
    if (val < std::numeric_limits<int>::min()) {
        throw ArithmeticException("Integer underflow: " + std::to_string(val) + " < " + std::to_string(std::numeric_limits<int>::min()), val);
    }
}

int IntegerType::bool_convert(bool val) {
    return val ? IntegerType::TRUE_VALUE : IntegerType::FALSE_VALUE;
}

bool IntegerType::is_true_value(int val) {
    return val != IntegerType::FALSE_VALUE;
}
