#pragma once

#include "TypeBase.h"

template <typename TypeClass>
class SingletonType : public TypeBase {
public:
    static std::shared_ptr<TypeClass> get() {
        static std::shared_ptr<TypeClass> instance(new TypeClass());
        return instance;
    };
};
