#pragma once

#include "RealTypeBase.h"
#include <string>

class IntegerValue;
class IntegerType : public RealTypeBase<IntegerValue, IntegerType, int> {
friend class SingletonType<IntegerType>;
public:
    bool is_true(const IntegerValue& value) const override;
    ValuePtr create_value(int value) const override;
    std::string type_name() const override;

    static ValuePtr create_false();
    static ValuePtr create_true();

private:
    static const int FALSE_VALUE = 0;
    static const int TRUE_VALUE = 1;

    IntegerType();

    static void check_value(int64_t val);
    static bool is_true_value(int val);
};
