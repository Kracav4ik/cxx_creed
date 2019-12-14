#include "CinValue.h"
#include "CinType.h"
#include "SpecialValue.hpp"

#include <iostream>

ValuePtr CinValue::binary_op(const std::string& op, const ValuePtr& right) const {
    if (op == "RSHIFT") {
        // std::cin >>  TODO: implement
        return std::const_pointer_cast<CinValue>(shared_from_this());
    }
    return SpecialValue::binary_op(op, right);
}

std::string CinValue::printable_str() const {
    return "[std::cin object]";
}
