#include "IntegerType.h"
#include "IntegerValue.h"

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
