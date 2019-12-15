#include "StringValue.h"

#include "RealValueBase.hpp"
#include "RealTypeBase.hpp"
#include "StringType.h"
#include "ValueVisitor.h"

#include <utility>

StringValue::StringValue(std::string  value) : RealValueBase(std::move(value)) {}

std::string StringValue::printable_str() const {
    return get_value();
}

void StringValue::visit(ValueVisitor& visitor) {
    visitor.visitStringValue(*this);
}
