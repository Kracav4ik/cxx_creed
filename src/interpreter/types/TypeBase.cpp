#include "TypeBase.h"
#include "ValueBase.h"

bool TypeBase::can_assign(ValuePtr ptr) const {
    return ptr->get_type().get() == this;  // TODO: is there a better way?
}
