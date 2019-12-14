#include "SpecialType.h"

template <typename TypeValue, typename TypeClass>
ValuePtr SpecialType<TypeValue, TypeClass>::create_empty_value() const {
    static std::shared_ptr<TypeValue> instance(new TypeValue());
    return instance;
}

template <typename TypeValue, typename TypeClass>
bool SpecialType<TypeValue, TypeClass>::can_assign(ValuePtr ptr) const {
    return false;
}
