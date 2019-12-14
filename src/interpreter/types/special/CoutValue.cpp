#include "CoutValue.h"
#include "CoutType.h"
#include "SpecialValue.hpp"

#include <iostream>

ValuePtr CoutValue::binary_op(const std::string& op, const ValuePtr& right) const {
    if (op == "LSHIFT") {
        std::cout << right->printable_str(); // TODO: use printer
        return std::const_pointer_cast<CoutValue>(shared_from_this());
    }
    return SpecialValue::binary_op(op, right);
}

std::string CoutValue::printable_str() const {
    return "[std::cout object]";
}
