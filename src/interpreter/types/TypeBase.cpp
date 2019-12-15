#include "TypeBase.h"
#include "ValueBase.h"
#include "IntegerType.h"

bool TypeBase::can_assign(ValuePtr ptr) const {
    return ptr->get_type().get() == this;  // TODO: is there a better way?
}

ValuePtr TypeBase::bool_convert(bool val) {
    return val ? IntegerType::create_true() : IntegerType::create_false();
}
