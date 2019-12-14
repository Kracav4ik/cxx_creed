#pragma once

#include "interpreter/types/SingletonType.h"

template <typename TypeValue, typename TypeClass>
class SpecialType : public SingletonType<TypeClass> {
public:
    ValuePtr create_empty_value() const override;
    bool can_assign(ValuePtr ptr) const override;
};
