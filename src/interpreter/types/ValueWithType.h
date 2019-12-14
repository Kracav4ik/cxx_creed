#pragma once

#include "ValueBase.h"

template <typename TypeClass>
class ValueWithType : public ValueBase {
public:
    TypePtr get_type() const final {
        return get_real_type();
    }

    static std::shared_ptr<TypeClass> get_real_type() {
        return TypeClass::get();
    }
};
