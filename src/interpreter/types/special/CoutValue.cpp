#include "CoutValue.h"
#include "CoutType.h"

#include "interpreter/exceptions/UnknownOpException.h"
#include <iostream>

ValuePtr CoutValue::binary_op(const std::string& op, const ValuePtr& right) const {
    if (op == "LSHIFT") {
        std::cout << right->printable_str(); // TODO: use printer
    } else {
        throw UnknownOpException("Unknown binary op token " + op);
    }
    return std::const_pointer_cast<CoutValue>(shared_from_this());
}

ValuePtr CoutValue::unary_op(const std::string& op) const {
    throw UnknownOpException("Unknown unary op token " + op);
}

bool CoutValue::is_true() const {
    return true;
}

std::string CoutValue::printable_str() const {
    return "[std::cout object]";
}

TypePtr CoutValue::get_type() const {
    return CoutType::get();
}
