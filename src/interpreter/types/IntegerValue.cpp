#include "IntegerValue.h"
#include "RealValueBase.hpp"
#include "RealTypeBase.hpp"
#include "IntegerType.h"
#include "ValueVisitor.h"

IntegerValue::IntegerValue(int value) : RealValueBase(value) {}

std::string IntegerValue::printable_str() const {
    return std::to_string(get_value());
}

void IntegerValue::visit(ValueVisitor& visitor) {
    visitor.visitIntegerValue(*this);
}
