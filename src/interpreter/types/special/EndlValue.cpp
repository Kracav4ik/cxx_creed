#include "EndlValue.h"
#include "EndlType.h"
#include "interpreter/exceptions/UnknownOpException.h"

ValuePtr EndlValue::binary_op(const std::string& op, const ValuePtr& right) const {
    throw UnknownOpException("Unknown binary op token " + op);
}

ValuePtr EndlValue::unary_op(const std::string& op) const {
    throw UnknownOpException("Unknown unary op token " + op);
}

bool EndlValue::is_true() const {
    return true;
}

std::string EndlValue::printable_str() const {
    return "\n";
}

TypePtr EndlValue::get_type() const {
    return EndlType::get();
}
