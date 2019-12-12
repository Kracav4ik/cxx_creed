#include "ValueBase.h"
#include "TypeBase.h"

#include <cassert>

ValuePtr ValueBase::binary_op(const std::string& op, const ValuePtr& right) const {
    assert(right);  // TODO: throw
    return get_type()->binary_op(*this, op, *right);
}

ValuePtr ValueBase::unary_op(const std::string& op) const {
    return get_type()->unary_op(op, *this);
}

bool ValueBase::is_true() const {
    return get_type()->is_true(*this);
}
