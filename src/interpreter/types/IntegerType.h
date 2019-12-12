#pragma once

#include "RealTypeBase.h"
#include <unordered_map>
#include <string>
#include <functional>

class IntegerValue;
class IntegerType : public RealTypeBase<IntegerValue, int> {
public:
    bool is_true(const IntegerValue& value) const override;
    ValuePtr create_value(int value) const override;
    std::string type_name() const override;

    ValuePtr create_false() const;
    ValuePtr create_true() const;

    static std::shared_ptr<IntegerType> get();

private:
    static const int FALSE_VALUE = 0;
    static const int TRUE_VALUE = 1;

    IntegerType();

    static void check_value(int64_t val);
    static int bool_convert(bool val);
    static bool is_true_value(int val);
};
